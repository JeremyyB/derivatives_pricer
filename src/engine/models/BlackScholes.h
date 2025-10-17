#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H
#include "Model.h"


class BlackScholes : public Model{
public:
    BlackScholes(int steps, int seed)
        : Model(steps, seed) {
    }

    explicit BlackScholes(int steps)
        : Model(steps) {
    }

    std::vector<double> simulatePaths() override;

    double priceEUCall(double S0, double K, double T, double r, double sigma) override;
};



#endif //BLACKSCHOLES_H
