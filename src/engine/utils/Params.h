#ifndef PARAMS_H
#define PARAMS_H
#include "engine/methods/PricingMethod.h"


struct PricingParams {
    virtual ~PricingParams() = default;

    virtual PricingMethod getMethodType() const = 0;
};

struct MonteCarloParams : public PricingParams {
    int simulations;
    int seed;
    int steps;

    MonteCarloParams(int simulations, int seed, int steps)
        : simulations(simulations), seed(seed), steps(steps) {
    }

    PricingMethod getMethodType() const override {
        return MTE_CARLO;
    }
};

struct BinomialParams : public PricingParams {
    int steps;

    double u;
    double d;

    // TODO : Enum default parameters DEFAULT_UP
    BinomialParams(int steps, double u, double d)
        : steps(steps),
          u(u),
          d(d) {
    }

    PricingMethod getMethodType() const override {
        return BINOMIAL;
    }
};

struct BlackScholesParams : public PricingParams {
    // No simulations here
    // Could be empty or contain other BlackScholes-specific parameters
    PricingMethod getMethodType() const override {
        return BLACK_SCHOLES;
    }
};


#endif //PARAMS_H
