#ifndef GEAR_PREDICTIVE_FILTER_H
#define GEAR_PREDICTIVE_FILTER_H

#include <../../eigen/Eigen/Dense>
#include <cmath>

#include "sensor_configs.h"
#include "sensor_utils.h"

class GearPredictiveFilter {
public:
    using TransitionProbabilities = struct TransitionProbabilities_t {
        double stay = 0.9; //!< probability of staying in gear
        double adjacent = 0.04; //!< probability of moving to adjacent gear
        double neutral = 0.015; //!< probability of clutching in or shifting to neutral
        double skip = 0.001; //!< probability of skipping a gear
        size_t numStates = 6; //!< number of states (default -> 5 gears + neutral)
    };

    using EstimatedGear = struct EstimatedGear_t {
        int index = 0;
        double confidence = 0;
        int neutralIndex = 0;
    };

    static constexpr double FIXED_NEUTRAL_LIKELIHOOD = 1.0e-6;
    static constexpr double DEFAULT_INITIAL_NEUTRAL_PROB = 0.9;
    static constexpr double DEFAULT_SIGMA_PCT = 0.03;

    using TransitionMatrix = Eigen::MatrixXd;
    using ProbabilityVector = Eigen::VectorXd;
    using LikelihoodVector = Eigen::VectorXd;
    using ValueVector = Eigen::VectorXd;
    using NoiseSigmaVector = Eigen::VectorXd;

    using MovingAvgFilter = struct MovingAvgFilter_t {
        MovingAvgFilter_t(size_t N) : buffer(N) {
        }

        Eigen::VectorXd buffer;
        int count = 0;
        size_t totalCount;

        double update(double val) {
            buffer(count) = val;
            count++;
            totalCount++;

            if (count >= buffer.size()) {
                count = 0;
            }

            auto sum = 0.0;
            for (const auto& val : buffer) {
                sum += val;
            }

            return sum / static_cast<double>(buffer.size());
        }
    };

    GearPredictiveFilter(const TransitionProbabilities& prob, const SensorConfig::GearIndicatorConfig_t& gearConfig) :
        mTransitionMatrix(prob.numStates, prob.numStates),
        mGearIndicatorConfig(gearConfig),
        mSpeedFilter(gearConfig.smoothingFilterN),
        mRpmFilter(gearConfig.smoothingFilterN),
        mNoiseSigmaVector(gearConfig.gearRatios.size()),
        mExpectedVector(gearConfig.gearRatios.size()),
        mProbVector(gearConfig.gearRatios.size() + 1) {
        // generate transition matrix
        generateTransitionMatrix(prob, mTransitionMatrix);

        // generate expected values
        generateExpectedValues(gearConfig, mExpectedVector);

        //generate noise sigma vector
        generateSigmaNoiseVector(mExpectedVector, DEFAULT_SIGMA_PCT, mNoiseSigmaVector);

        //generate initial probabilities
        generateInitialProbablilities(gearConfig, mProbVector);
    }

    bool isValidInput(double observedSpeed, double observedRpm) {
        return (observedSpeed > mGearIndicatorConfig.speedDropOut && observedRpm > mGearIndicatorConfig.idleHighRpm);
    }

    int fallbackProbability(Eigen::VectorXd& prob) {
        if (prob.size() != mTransitionMatrix.cols()) {
            return -1;
        }

        prob(0) = 1.0;
        for (auto i = 1; i < prob.size(); i++) {
            prob(i) = 0.0;
        }

        return 0;
    }

    static constexpr double calculateLikelihood(double observed, double mean, double sigmaNoise) {
        auto norm = 1 / std::sqrt( 2 * M_PI * sigmaNoise * sigmaNoise );
        auto exponent = -0.5 * (observed - mean) * (observed - mean) / (sigmaNoise * sigmaNoise);

        return norm * std::exp(exponent);
    }

    static int generateLikelihoodVector(double observed, const ValueVector& expectedValues, const NoiseSigmaVector& sigmaNoiseVector, LikelihoodVector& likelihood) {
        if (expectedValues.size() != sigmaNoiseVector.size()) {
            return -1;
        }

        if (likelihood.size() != expectedValues.size() + 1) {
            return -1;
        }

        likelihood(0) = FIXED_NEUTRAL_LIKELIHOOD;
        for (int i = 1; i < likelihood.size(); i++) {
            likelihood(i) = calculateLikelihood(observed, expectedValues(i-1), sigmaNoiseVector(i-1));
        }

        return 0;
    }

    int flattenLikelihood(LikelihoodVector& likelihoods, double offset = 0.1) {
        if (likelihoods.size() < mTransitionMatrix.cols()) {
            return -1;
        }

        for (auto& val : likelihoods) {
            val = (val * 0.5) + offset;
        }

        return 0;
    }

    static constexpr int generateTransitionMatrix(TransitionProbabilities prob, TransitionMatrix& transitionMatrix) {
        for (size_t row = 0; row < prob.numStates; row++) {
            if (row == 0) {
                for (size_t col = 0; col < prob.numStates; col++) {
                    // neutral
                    transitionMatrix(row, col) = (col == 0) ? prob.stay : (1-prob.stay) / (prob.numStates-1);
                }
            } else {
                for (size_t col = 0; col < prob.numStates; col++) {
                    transitionMatrix(row, col) = prob.skip;
                }
                // current gear
                transitionMatrix(row, row) = prob.stay;
                transitionMatrix(row, 0) = prob.neutral;

                if (row > 1) { // not in first gear
                    transitionMatrix(row, row - 1) = prob.adjacent;
                } else {
                    transitionMatrix(row, row) += prob.adjacent;
                }

                if (row < (prob.numStates-1)) { // not in top gear
                    transitionMatrix(row, row + 1) = prob.adjacent;
                } else {
                    transitionMatrix(row, row) += prob.adjacent;
                }
            }
            double rowSum = 0;
            for(size_t col = 0; col < prob.numStates; col++) {
                rowSum += transitionMatrix(row,col);
            }

            // normalize
            for (size_t col = 0; col < prob.numStates; col++) {
                transitionMatrix(row,col) /= rowSum;
            }
        }

        return 0;
    }

    static int generateExpectedValues(const SensorConfig::GearIndicatorConfig_t& gearConfig, ValueVector& expectedValues) {
        if (expectedValues.size() != gearConfig.gearRatios.size()) {
            return -1;
        }

        auto rearEnd = gearConfig.rearEndRatio;
        auto tireDiameterMiles = SensorUtils::toMiles(gearConfig.tireDiameter, gearConfig.tireDiameterUnits);

        for (int i = 0; i < gearConfig.gearRatios.size(); i++) {
            expectedValues(i) = (gearConfig.gearRatios[i] * rearEnd) / (60.0 * tireDiameterMiles * M_PI);
        }

        return 0;
    }

    static int generateInitialProbablilities(
        const SensorConfig::GearIndicatorConfig_t& gearConfig,
        ProbabilityVector& prob,
        double neutralProb = DEFAULT_INITIAL_NEUTRAL_PROB) {

        if (prob.size() != gearConfig.gearRatios.size() + 1) {
            return -1;
        }

        auto numGears = gearConfig.gearRatios.size();

        prob(0) = neutralProb;
        for (int i = 1; i < prob.size(); i++) {
            prob(i) = (1 - prob(0)) / numGears;
        }

        return 0;
    }

    static int generateSigmaNoiseVector(const ValueVector& expectedValues, double noisePct, NoiseSigmaVector& noiseVector) {
        if (expectedValues.size() != noiseVector.size()) {
            return -1;
        }

        for (int i = 0; i < expectedValues.size(); i++) {
            noiseVector(i) = expectedValues(i) * noisePct;
        }

        return 0;
    }

    EstimatedGear update(double observedSpeedMph, double observedRpm) {
        auto filteredSpeed = mSpeedFilter.update(observedSpeedMph);
        auto filteredRpm = mRpmFilter.update(observedRpm);
        auto speedDropOutMph = SensorUtils::toMph(mGearIndicatorConfig.speedDropOut, mGearIndicatorConfig.speedDropOutUnits);
        auto observedRatio = 0.0;

        // make sure we're going fast enough to even estimate
        if (filteredSpeed < speedDropOutMph || filteredRpm < mGearIndicatorConfig.idleHighRpm) {
            fallbackProbability(mProbVector);
        }

        // make sure that we're not trying to divide by a very small number
        if (filteredSpeed > 0.1) {
            observedRatio = filteredRpm / filteredSpeed;
        }

        // calculate likelihoods
        LikelihoodVector likelihood = LikelihoodVector(mProbVector.size());
        generateLikelihoodVector(observedRatio, mExpectedVector, mNoiseSigmaVector, likelihood);
        if (filteredSpeed < speedDropOutMph) {
            flattenLikelihood(likelihood);
        }

        // calculate posterior probabilities
        ProbabilityVector posterior = ProbabilityVector(mProbVector.size());
        posterior = likelihood.cwiseProduct(mProbVector);

        // make sure we don't try to divide by zero when making the posterior PDF
        if (posterior.sum() == 0) {
            fallbackProbability(posterior);
        } else {
            posterior = posterior / posterior.sum();
        }

        // estimate gear
        Eigen::Index maxIndex;
        double confidence = posterior.maxCoeff(&maxIndex);

        EstimatedGear ret = {
            .index = static_cast<int>(maxIndex - 1),
            .confidence = confidence,
            .neutralIndex = 0
        };

        //predict next state
        mProbVector = posterior * mTransitionMatrix;
        mProbVector = mProbVector / mProbVector.sum();

        return ret;
    }


private:
    TransitionMatrix mTransitionMatrix;
    const SensorConfig::GearIndicatorConfig_t mGearIndicatorConfig;
    MovingAvgFilter mSpeedFilter;
    MovingAvgFilter mRpmFilter;
    NoiseSigmaVector mNoiseSigmaVector;
    ValueVector mExpectedVector;
    ProbabilityVector mProbVector;
};

#endif // GEAR_PREDICTIVE_FILTER_H
