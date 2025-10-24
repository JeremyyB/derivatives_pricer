#include "cfd.h"

double CFD::payoff(double S1) {
    return (S1 - S0) * position;
}

double CFD::price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) {
    return -1; // TODO
}

py::array_t<double> CFD::greeks(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) {
    py::array_t<double> result({5, 1});
    return result; // TODO
}
