#ifndef GEAR_PREDICTIVE_FILTER_H
#define GEAR_PREDICTIVE_FILTER_H

#include <vector>
#include <../../eigen/Eigen/Dense>

class GearPredictiveFilter {
public:
    using TransitionProbabilities = struct TransitionProbabilities_t {
        double stay = 0.9; //!< probability of staying in gear
        double adjacent = 0.04; //!< probability of moving to adjacent gear
        double neutral = 0.015; //!< probability of clutching in or shifting to neutral
        double skip = 0.001; //!< probability of skipping a gear
        size_t numStates = 6; //!< number of states (default -> 5 gears + neutral)
    };
    using TransitionMatrix = Eigen::MatrixXd;

    GearPredictiveFilter(size_t N) {}


    static int generateTransitionMatrix(TransitionProbabilities prob, TransitionMatrix& transitionMatrix) {
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

};

#endif // GEAR_PREDICTIVE_FILTER_H
