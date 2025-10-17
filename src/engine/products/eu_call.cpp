#include "eu_call.h"

#include <algorithm>

double call_payoff(double S, double K) {
    return std::max(S - K, 0.);
}
