#ifndef BINOMIAL_H
#define BINOMIAL_H
#include "Model.h"


class Binomial : public Model {
public:
    double u;
    double d;

    Binomial(int simulations, double u, double d)
        : Model(simulations),
          u(u), d(d) {
    }

    py::array_t<double> simulatePaths(double S0, double r, double sigma) override;

    double priceEUCall(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> computeGreek(Greeks greek, double S0, double K, double T, double r, double sigma) override;

protected:
    py::array_t<double> delta(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> gamma(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> theta(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> vega(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> rho(double S0, double K, double T, double r, double sigma) override;
};


#endif //BINOMIAL_H
