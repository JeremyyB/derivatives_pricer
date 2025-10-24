#include "eu_put.h"

#include <algorithm>

#include "engine/models/Binomial.h"
#include "engine/models/BlackScholes.h"
#include "engine/models/MonteCarlo.h"

double EUPut::payoff(double S1) {
    return std::max(strike - S1, 0.) * position;
}

double EUPut::price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) {
    double res = -1;
    switch (methodsParams->getMethodType()) {
        case MTE_CARLO: {
            std::shared_ptr<MonteCarloParams> pricing_params = std::dynamic_pointer_cast<MonteCarloParams>(methodsParams);
            MonteCarlo model = MonteCarlo(pricing_params->steps, pricing_params->simulations, pricing_params->seed);
            res = model.priceEUPut(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
        case BLACK_SCHOLES: {
            BlackScholes model = BlackScholes();
            res = model.priceEUPut(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
        case BINOMIAL: {
            std::shared_ptr<BinomialParams> pricing_params = std::dynamic_pointer_cast<BinomialParams>(methodsParams);
            Binomial model = Binomial(pricing_params->steps, pricing_params->u, pricing_params->d);
            res = model.priceEUPut(S0, strike, timeToMaturity, riskfree_rate, vol);
        }
            break;
    }
    return position * res;
};