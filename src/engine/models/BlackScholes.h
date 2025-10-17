#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H
#include "Model.h"


class BlackScholes : public Model {
public:
    BlackScholes(int steps, int seed)
    // TODO : Remove these constructor, BS needs none of those two parameters, set them to NaN
        : Model(steps, seed) {
    }

    explicit BlackScholes(int steps)
        : Model(steps) {
    }

    std::vector<double> simulatePaths(double S0, double param1, double param2) override;

    double priceEUCall(double S0, double K, double T, double r, double sigma) override;
};


#endif //BLACKSCHOLES_H
