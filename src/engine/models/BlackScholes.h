#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H
#include "Model.h"


class BlackScholes : public Model {
public:
    BlackScholes() = default;

    py::array_t<double> simulatePaths(double S0, double param1, double param2) override;

    double priceEUCall(double S0, double K, double T, double r, double sigma) override;
};


#endif //BLACKSCHOLES_H
