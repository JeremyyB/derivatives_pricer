#include "cfd.h"

double CFD::payoff(double S1) {
    return (S1 - S0) * position;
}

double CFD::price(double vol, double riskfree_rate, PricingMethod method) {
    return -1 ; // TODO
}
