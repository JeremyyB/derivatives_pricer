#include "eu_put.h"

#include <algorithm>

#include "engine/models/BlackScholes.h"

double EUPut::payoff(double S1) {
    return std::max(strike - S1, 0.) * position;
}

double EUPut::price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) {
    double res = -1;
    switch (methodsParams->getMethodType()) {
        case MTE_CARLO:
            // TODO
            break;
        case BLACK_SCHOLES: {
            BlackScholes model = BlackScholes();
            res = model.priceEUPut(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
        case BINOMIAL:
            // TODO
            break;
    }
    return position * res;
};