#include "MonteCarlo.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <random>

namespace py = pybind11;


py::array_t<double> MonteCarlo::simulatePaths(double S0, double r, double sigma) {
    py::array_t<double> result({this->simulations, this->steps});
    auto buf = result.mutable_unchecked<2>();

    std::mt19937 generator(this->seed);
    std::normal_distribution<double> normal(0.0, 1.0);

    double dt = 1.0 / this->steps;
    double sqrtdt = std::sqrt(dt);

    // Initialize the first step for all simulations
    for (ssize_t sim = 0; sim < this->simulations; sim++) {
        buf(sim, 0) = S0;
    }

    // Generate paths directly into np buffer
    for (ssize_t sim = 0; sim < this->simulations; sim++) {
        for (ssize_t i = 1; i < this->steps; i++) {
            double dB = normal(generator) * sqrtdt;
            buf(sim, i) = buf(sim, i - 1) * std::exp((r - 0.5 * sigma * sigma) * dt + sigma * dB);
        }
    }
    return result;
}


double MonteCarlo::priceEUCall(double S0, double K, double T, double r, double sigma) {
    // Simulate paths
    py::array_t<double> paths = this->simulatePaths(S0, r, sigma);
    auto paths_buf = paths.unchecked<2>();

    // Sum payoffs from final values
    double sum_payoffs = .0;
    for (ssize_t sim = 0; sim < this->simulations; sim++) {
        double ST = paths_buf(sim, this->steps - 1);
        sum_payoffs += std::max(ST - K, 0.0);
    }

    // Average and discount
    double mean_payoff = sum_payoffs / this->simulations;
    return mean_payoff * std::exp(-r * T);
}
