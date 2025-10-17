#include "BlackScholes.h"

std::vector<double> BlackScholes::simulatePaths() {
    return {.0};
}

double BlackScholes::priceEUCall(double S0, double K, double T, double r, double sigma) {
    double d1 = (std::log(S0 / K) + (r + sigma * sigma / 2) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    double N_d1 = 0.5 * (1 + std::erf(d1 / std::sqrt(2)));
    double N_d2 = 0.5 * (1 + std::erf(d2 / std::sqrt(2)));

    return S0 * N_d1 - K * std::exp(-r * T) * N_d2;
}
