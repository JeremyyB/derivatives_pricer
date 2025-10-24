#include "Binomial.h"

#include "engine/products/eu_call.h"

py::array_t<double> Binomial::simulatePaths(double S0, double r, double sigma) {
    py::array_t<double> result({this->steps + 1, this->steps + 1});
    auto buf = result.mutable_unchecked<2>();

    for (ssize_t i = 1; i <= this->steps; i++) {
        for (ssize_t j = 1; j <= i; j++) {
            buf(i, j) = S0 * pow(this->u, j) * pow(this->d, i - j);
        }
    }
    return result;
}


double Binomial::priceEUCall(double S0, double K, double T, double r, double sigma) {
    py::array_t<double> price_lattice = this->simulatePaths(S0, r, sigma);
    auto prices = price_lattice.unchecked<2>();

    double dt = T / this->steps;
    double disc = exp(-r * dt);
    double p = (exp(r * dt) - this->d) / (this->u - this->d);

    py::array_t<double> opt_lattice({this->steps + 1, this->steps + 1});
    auto opt = opt_lattice.mutable_unchecked<2>();

    for (ssize_t j = 0; j <= this->steps; ++j) {
        opt(this->steps, j) = EUCall(S0, K, T, 1., "")
                .payoff(prices(this->steps, j));
    }

    for (ssize_t i = this->steps - 1; i >= 0; --i) {
        for (ssize_t j = 0; j <= i; ++j) {
            opt(i, j) = disc * (p * opt(i + 1, j + 1) + (1.0 - p) * opt(i + 1, j));
        }
    }
    return opt(0, 0);
}
