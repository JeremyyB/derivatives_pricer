#include "eu_call.h"

#include <algorithm>

#include "engine/methods/PricingMethod.h"
#include "engine/models/BlackScholes.h"
#include "engine/models/Model.h"


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
            BlackScholes model = BlackScholes(-1, -1);
            res = model.priceEUCall(S0, strike, timeToMaturity, riskfree_rate, vol);
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