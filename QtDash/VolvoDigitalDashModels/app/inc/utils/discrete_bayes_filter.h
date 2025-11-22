#ifndef DISCRETE_BAYES_FILTER_H
#define DISCRETE_BAYES_FILTER_H

#include <QString>
#include <QVector>
#include <QtMath>

class DiscreteBayesFilter {
public:
    static constexpr size_t ChangeN = 4;
    using Output = struct Output_t {
        size_t index = 0;
        qreal confidence = 0;
        bool defaultEnabled = true;
    };

    using DefaultState = struct DefaultState_t {
        qreal initialProbability = 0.9;
        qreal fixedLikelihood = 1.0e-6;
        bool enabled = true;
    };

    DiscreteBayesFilter(bool enableDefaultState = true, qreal defaultStateProb = 0.9, size_t filterN = 4)
        : mFilterN(filterN), mDefaultState({defaultStateProb, 1.0e-6, enableDefaultState}) {}

    int init(const QVector<qreal>& TExpected, qreal noiseSigmaPct = 0.03) {
        if (TExpected.isEmpty()) {
            return -1;
        }

        QVector<qreal> initialProb;
        if (auto ret = setupInitialProbabilities(TExpected.size(), initialProb); ret != 0) {
            return ret;
        }

        // Fill expected state values
        for (auto& val : TExpected) {
            mTExpected.push_back(val);
            mNoiseSigma.push_back(val * noiseSigmaPct);
        }

        // populate initial probabilities
        auto sum = 0.0;
        for (auto& val : initialProb) {
            sum += val;
            mProb.push_back(val);
        }

        // Probabilities must be a PDF
        if (sum != 1.0) {
            return -1;
        }

        return 0;
    }

    int update(const qreal TObserved, Output& output) {
        // posterior probabilities
        QVector<qreal> posterior;
        calculatePosterior(TObserved, posterior);

        // calculate the sum so we can make the posterior a PDF
        if (auto ret = normalize(posterior); ret != 0) {
            return -1;
        }

        // divide by sum to make posterior a PDF and find the max index
        mProb.clear();
        auto maxVal = 0;
        auto maxIndex = 0;
        auto ind = 0;
        for (auto& val : posterior) {
            mProb.push_back(val);

            if (mProb.back() > maxVal) {
                maxVal = mProb.back();
                maxIndex = ind;
            }
            ind++;
        }

        output.index = maxIndex;
        output.confidence = mProb[maxIndex];
        output.defaultEnabled = mDefaultState.enabled;

        // change must persist to be valid
        if (mInitialUpdate) {
            mPreviousOutput = output;
            mContinuousCount = 0;
            mInitialUpdate = false;
        } else {
            if (mPreviousOutput.index == output.index) {
                mContinuousCount = 0;
            } else {
                mContinuousCount++;
                if (mContinuousCount < ChangeN) {
                    output = mPreviousOutput;
                } else {
                    mContinuousCount = 0;
                }
            }
        }

        // add noise so we don't get locked in if one state is 0 or 1
        for (auto& val : mProb) {
            val += mTransitionNoise;
        }

        // re-normalize
        if (auto ret = normalize(mProb); ret != 0) {
            return -1;
        }
        return 0;
    }

private:
    QVector<qreal> mProb;
    QVector<qreal> mNoiseSigma;
    QVector<qreal> mTExpected;

    qreal mTransitionNoise = 0.1f;
    size_t mContinuousCount = 5;
    size_t mFilterN = 4;

    bool mInitialUpdate = true;
    Output mPreviousOutput;

    DefaultState mDefaultState;

    int setupInitialProbabilities(size_t N, QVector<qreal>& initialProbabilities) {
        if (!initialProbabilities.isEmpty()) {
            return -1;
        }

        auto remainingProbability = 1.0;
        if (mDefaultState.enabled) {
            initialProbabilities.push_back(mDefaultState.initialProbability);
            remainingProbability = 1.0 - mDefaultState.initialProbability;
        }

        for (size_t i = 0; i < N; i++) {
            initialProbabilities.push_back(remainingProbability / static_cast<qreal>(N));
        }

        return 0;
    }

    int calculatePosterior(qreal TObserved, QVector<qreal>& posterior) {
        if (!posterior.isEmpty()) {
            return -1;
        }

        // add the fixed likelihood for the default state
        if (mDefaultState.enabled) {
            posterior.push_back(mDefaultState.fixedLikelihood);
        }

        // calculate likelihoods based on the observation
        for (auto i = 0; i < mTExpected.size(); i++) {
            auto sigma = mNoiseSigma[i];
            auto deltaT = TObserved - mTExpected[i];

            auto norm = 1 / (qSqrt(2 * M_PI * sigma * sigma));
            auto exponent = -0.5 * (deltaT * deltaT) / (sigma * sigma);

            auto likelihood = norm * qExp(exponent);

            // update probabilities
            posterior.push_back(likelihood * mProb[i]);
        }

        return 0;
    }

    int normalize(QVector<qreal>& vals) {
        auto sum = 0.0;
        for (const auto& val : vals) {
            sum += val;
        }

        if (sum == 0.0) {
            return -1;
        }

        for (auto& val : vals) {
            val /= sum;
        }
        return 0;
    }
};

#endif // DISCRETE_BAYES_FILTER_H
