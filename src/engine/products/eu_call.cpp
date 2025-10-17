#include "eu_call.h"

#include <algorithm>

#include "engine/methods/PricingMethod.h"


double EUCall::payoff(double S1) {
    return std::max(S1 - strike, 0.) * position;
}

double EUCall::price(double vol, double riskfree_rate, PricingMethod method) {
    double res = -1;
    switch (method) {
        case MTE_CARLO:
            // TODO
            break;
        case BLACK_SCHOLES: {
            double r = riskfree_rate;
            double sigma = vol;
            double T = timeToMaturity;
            double K = strike;

            double d1 = (std::log(S0 / K) + (r + sigma * sigma / 2) * T) / (sigma * std::sqrt(T));
            double d2 = d1 - sigma * std::sqrt(T);

            double N_d1 = 0.5 * (1 + std::erf(d1 / std::sqrt(2)));
            double N_d2 = 0.5 * (1 + std::erf(d2 / std::sqrt(2)));

            res = S0 * N_d1 - K * std::exp(-r * T) * N_d2;
        }
            break;
        case BINOMIAL:
            // TODO
            break;
    }
    return(res);
}
/*
double greeks(double S0, double K, GreekType greek, Struct parameterOfPricing) {

}
*/