#ifndef MODEL_H
#define MODEL_H
#include <vector>

#include "engine/products/Derivative.h"

inline int DEFAULT_NB_STEPS = 100; // TODO : Convert me into an enum
inline int DEFAULT_SEED = 123456789; // TODO : Convert me into an enum

class Model {
public:
    int steps = DEFAULT_NB_STEPS; // steps = n° of Monte-Carlo simulation, or n° of Binomial-steps
    int seed = DEFAULT_SEED;

    Model(int steps, int seed)
        : steps(steps),
          seed(seed) {
    }

    explicit Model(int steps)
        : steps(steps) {
    }

    Model() = default;

    virtual ~Model() = default;

    // TODO : Make it returns a numpy array instead for performance boost
    virtual std::vector<double> simulatePaths(double S0, double param1, double param2) = 0;

    virtual double priceEUCall(double S0, double K, double T, double r, double sigma) = 0;

    double priceEUPut(double S0, double K, double T, double r, double sigma);
};

#endif //MODEL_H
