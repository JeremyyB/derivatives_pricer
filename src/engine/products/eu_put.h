#ifndef EU_PUT_H
#define EU_PUT_H
#include "Derivative.h"

class EUPut : public Derivative {
public:
    EUPut(double s0, double strike, double time_to_maturity, double position, const std::string &underlying_id)
        : Derivative(s0, strike, time_to_maturity, position, underlying_id) {
    }

    double payoff(double S1) override;

    double price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) override;
};


#endif //EU_PUT_H
