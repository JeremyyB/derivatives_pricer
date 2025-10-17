#include <iostream>
#include <pybind11/pybind11.h>

#include "engine/products/eu_call.h"
#include "engine/products/eu_put.h"

PYBIND11_MODULE(derivatives_pricer, m) {
    m.def("call_payoff", &call_payoff);
    m.def("put_payoff", &put_payoff);
}
