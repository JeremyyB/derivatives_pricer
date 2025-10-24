#ifndef STRANGLE_H
#define STRANGLE_H
#include "Derivative.h"


class Strangle : public Derivative {
public:
    double Kput;
    double Kcall;

    Strangle(double s0, double time_to_maturity, double position, const std::string &underlying_id,
             double kput, double kcall)
        : Derivative(s0, NAN, time_to_maturity, position, underlying_id),
          Kput(std::min(kput, kcall)),
          Kcall(std::max(kput, kcall)) {
    }

    double payoff(double S1) override;

    double price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) override;

    py::array_t<double> greeks(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParams) override;
};


#endif //STRANGLE_H
