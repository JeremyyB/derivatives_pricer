#include <pybind11/pybind11.h>

#include "engine/methods/PricingMethod.h"

#ifndef DERIVATIVE_H
#define DERIVATIVE_H

namespace py = pybind11;

class Derivative {
public:
    virtual ~Derivative() = default;

    double S0;
    double strike;
    double timeToMaturity;
    double position; // 1 for long, -1 for short
    std::string underlyingId;

    Derivative(double s0, double strike, double time_to_maturity, double position,
               const std::string &underlying_id)
        : S0(s0),
          strike(strike),
          timeToMaturity(time_to_maturity),
          position(position),
          underlyingId(underlying_id) {
    }

    virtual double payoff(double S1) = 0;

    virtual double price(double vol, double riskfree_rate, PricingMethod method) = 0;
};


#endif //DERIVATIVE_H
