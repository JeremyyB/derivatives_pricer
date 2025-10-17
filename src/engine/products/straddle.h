//
// Created by JSB on 17/10/2025.
//

#ifndef STRADDLE_H
#define STRADDLE_H
#include "strangle.h"


class Straddle : public Strangle  {
public:
    Straddle(double s0, double strike, double time_to_maturity, double position, const std::string &underlying_id)
        : Strangle(s0, time_to_maturity, position, underlying_id, strike, strike) {
    }
};



#endif //STRADDLE_H
