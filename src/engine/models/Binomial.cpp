#include "Binomial.h"

py::array_t<double> Binomial::simulatePaths(double S0, double r, double sigma) {
    return py::array_t<double>({0, 0}); // TODO
}

double Binomial::priceEUCall(double S0, double K, double T, double r, double sigma) {
    return -1.; // TODO
}
