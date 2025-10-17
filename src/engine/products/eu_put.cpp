#include "eu_put.h"

#include <algorithm>

double EUPut::payoff(double S1) {
    return std::max(strike - S1, 0.) * position;
}

double EUPut::price(double vol, double riskfree_rate, PricingMethod method) {
    return -1; // TODO
}
