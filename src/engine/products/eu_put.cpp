#include "eu_put.h"

#include <algorithm>

double put_payoff(double S, double K) {
    return std::max(K - S, 0.);
}
