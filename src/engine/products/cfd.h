#ifndef CFD_H
#define CFD_H
#include "Derivative.h"


class CFD : public Derivative {
public:
    CFD(double s0, double strike, double time_to_maturity, double position, const std::string &underlying_id)
        : Derivative(s0, strike, time_to_maturity, position, underlying_id) {
    }

    double payoff(double S1) override;

    double price(double vol, double riskfree_rate, PricingMethod method) override;
};

#endif //CFD_H
