#include "eu_call.h"

#include <algorithm>

#include "engine/methods/PricingMethod.h"
#include "engine/models/Binomial.h"
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
            std::shared_ptr<MonteCarloParams> pricing_params = std::dynamic_pointer_cast<MonteCarloParams>(methodsParams);
            MonteCarlo model = MonteCarlo(pricing_params->steps, pricing_params->simulations, pricing_params->seed);
            res = model.priceEUCall(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
        case BLACK_SCHOLES: {
            BlackScholes model = BlackScholes();
            res = model.priceEUCall(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
        case BINOMIAL: {
            std::shared_ptr<BinomialParams> pricing_params = std::dynamic_pointer_cast<BinomialParams>(methodsParams);
            Binomial model = Binomial(pricing_params->steps, pricing_params->u, pricing_params->d);
            res = model.priceEUCall(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
    }
    return position * res;
}
/*
double greeks(double S0, double K, GreekType greek, Struct parameterOfPricing) {

}
*/