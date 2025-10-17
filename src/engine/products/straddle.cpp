#include "straddle.h"


class Straddle : public Strangle  {
public:
    Straddle(double s0, double strike, double time_to_maturity, double position, const std::string &underlying_id)
        : Strangle(s0, time_to_maturity, position, underlying_id, strike, strike) {
    }
};