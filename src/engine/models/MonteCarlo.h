#ifndef MONTECARLO_H
#define MONTECARLO_H


#include "Model.h"

class MonteCarlo : public Model {
public:
    int simulations; // TODO : Add a default value
    // By default, MTE_CARLO will be Naive Monte-Carlo, child will be variance-reduction upgrades
    MonteCarlo(int steps, int simulations, int seed)
        : Model(steps, seed),
          simulations(simulations) {
    }

    explicit MonteCarlo(int steps, int simulations)
        : Model(steps), simulations(simulations) {
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


#endif //MONTECARLO_H
