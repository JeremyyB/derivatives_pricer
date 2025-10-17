#include "MonteCarlo.h"

#include <random>


std::vector<double> MonteCarlo::simulatePaths(double S0, double r, double sigma) {
    // TODO : One has to verify that (why we use r & not mu / risk neutral v.s. observed)
    // TODO : Simulate multiple paths
    std::mt19937 generator(this->seed);
    std::normal_distribution<double> normal(0.0, 1.0);
    std::vector<double> path(this->steps);

    double dt = 1.0 / this->steps;
    double sqrtdt = std::sqrt(dt);

    path[0] = S0;

    for (int i = 1; i < this->steps; i++) {
        double dB = normal(generator) * sqrtdt;
        // Use risk-neutral drift r and volatility sigma
        path[i] = path[i - 1] * std::exp((r - 0.5 * sigma * sigma) * dt + sigma * dB);
    }

    return path;

}

double MonteCarlo::priceEUCall(double S0, double K, double T, double r, double sigma) {
    return .0;
}
