//
// Created by JSB on 17/10/2025.
//

#include "strangle.h"

#include "engine/models/BlackScholes.h"

double Strangle::payoff(double S1) {
    return (std::max(Kput - S1, 0.) + std::max( S1 - Kcall, 0.)) * position;
}

double Strangle::price(double vol, double riskfree_rate, PricingMethod method) {
    double res = -1;
    switch (method) {
        case MTE_CARLO:
            // TODO
            break;
        case BLACK_SCHOLES: {
            BlackScholes model = BlackScholes(-1, -1);
            double call_price = model.priceEUCall(S0, Kcall, timeToMaturity, riskfree_rate, vol);
            double put_price = model.priceEUPut(S0, Kput, timeToMaturity, riskfree_rate, vol);
            res = call_price + put_price;
        }
            break;
        case BINOMIAL:
            // TODO
            break;
    }
    return position * res;
}
