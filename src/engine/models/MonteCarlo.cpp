#include "MonteCarlo.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <random>

namespace py = pybind11;


py::array_t<double> MonteCarlo::simulatePaths(double S0, double r, double sigma) {
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

    auto result = pybind11::array_t<double>(this->steps);
    std::memcpy(result.mutable_data(), path.data(), path.size() * sizeof(double));
    return result;
}

double MonteCarlo::priceEUCall(double S0, double K, double T, double r, double sigma) {
    return .0;
}
