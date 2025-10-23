#include "eu_call.h"

#include <algorithm>

#include "engine/methods/PricingMethod.h"
#include "engine/models/BlackScholes.h"
#include "engine/models/Model.h"
#include "engine/models/MonteCarlo.h"


double EUCall::payoff(double S1) {
    return std::max(S1 - strike, 0.) * position;
}

double EUCall::price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) {
    double res = -1;
    switch (methodsParams->getMethodType()) {
        case MTE_CARLO: {
            std::shared_ptr<MonteCarloParams> pricing_params = std::dynamic_pointer_cast<MonteCarloParams>(methodsParams); // TODO : Check if casting is mandatory
            MonteCarlo model = MonteCarlo(pricing_params->steps, pricing_params->simulations, pricing_params->seed);
            res = model.priceEUCall(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
        case BLACK_SCHOLES: {
            BlackScholes model = BlackScholes();
            res = model.priceEUCall(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
        case BINOMIAL:
            // TODO
            break;
    }
    return position * res;
}
/*
double greeks(double S0, double K, GreekType greek, Struct parameterOfPricing) {

}
*/