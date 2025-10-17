#include "cfd.h"

double cfd_payoff(double S0, double S1, double K) {
    return (S1 - S0) * K;
}
