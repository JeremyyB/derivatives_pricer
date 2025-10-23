#ifndef CFD_H
#define CFD_H
#include "Derivative.h"


class CFD : public Derivative {
public:
    CFD(double s0, double time_to_maturity, double position, const std::string &underlying_id)
        : Derivative(s0, NAN, time_to_maturity, position, underlying_id) {
    }

    double payoff(double S1) override;

    double price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) override;
};

#endif //CFD_H
