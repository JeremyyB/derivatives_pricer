#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H
#include "Model.h"


class BlackScholes : public Model {
public:
    BlackScholes() = default;

    py::array_t<double> simulatePaths(double S0, double param1, double param2) override;

    double priceEUCall(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> computeGreek(Greeks greek, double S0, double K, double T, double r, double sigma) override;

protected:
    py::array_t<double> delta(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> gamma(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> theta(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> vega(double S0, double K, double T, double r, double sigma) override;

    py::array_t<double> rho(double S0, double K, double T, double r, double sigma) override;
};


#endif //BLACKSCHOLES_H
