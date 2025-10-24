#include "strangle.h"

#include "engine/models/Binomial.h"
#include "engine/models/BlackScholes.h"
#include "engine/models/MonteCarlo.h"

double Strangle::payoff(double S1) {
    return (std::max(Kput - S1, 0.) + std::max(S1 - Kcall, 0.)) * position;
}

double Strangle::price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) {
    double res = -1;
    switch (methodsParams->getMethodType()) {
        case MTE_CARLO: {
            std::shared_ptr<MonteCarloParams> pricing_params = std::dynamic_pointer_cast<MonteCarloParams>(methodsParams);
            MonteCarlo model = MonteCarlo(pricing_params->steps, pricing_params->simulations, pricing_params->seed);
            double call_price = model.priceEUCall(S0, Kcall, timeToMaturity, riskfree_rate, vol);
            double put_price = model.priceEUPut(S0, Kput, timeToMaturity, riskfree_rate, vol);
            res = call_price + put_price;
        }
            break;
        case BLACK_SCHOLES: {
            BlackScholes model = BlackScholes();
            double call_price = model.priceEUCall(S0, Kcall, timeToMaturity, riskfree_rate, vol);
            double put_price = model.priceEUPut(S0, Kput, timeToMaturity, riskfree_rate, vol);
            res = call_price + put_price;
        }
        break;
        case BINOMIAL: {
            std::shared_ptr<BinomialParams> pricing_params = std::dynamic_pointer_cast<BinomialParams>(methodsParams);
            Binomial model = Binomial(pricing_params->steps, pricing_params->u, pricing_params->d);
            double call_price = model.priceEUCall(S0, Kcall, timeToMaturity, riskfree_rate, vol);
            double put_price = model.priceEUPut(S0, Kput, timeToMaturity, riskfree_rate, vol);
            res = call_price + put_price;
        }
            break;
    }
    return position * res;
}
