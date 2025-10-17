#include <iostream>
#include <pybind11/pybind11.h>

#include "engine/products/cfd.h"
#include "engine/products/Derivative.h"
#include "engine/products/eu_call.h"
#include "engine/products/eu_put.h"

namespace py = pybind11;

// Trampoline class for Derivative
class PyDerivative : public Derivative {
public:
    using Derivative::Derivative; // inherit constructors

    double payoff(double S1) override {
        PYBIND11_OVERRIDE_PURE(double, Derivative, payoff, S1);
    }

    double price(double vol, double riskfree_rate, PricingMethod method) override {
        PYBIND11_OVERRIDE_PURE(double, Derivative, price, vol, riskfree_rate, method);
    }
};

PYBIND11_MODULE(derivatives_pricer, m) {
    py::class_<Derivative, PyDerivative /* trampoline */>(m, "Derivative")
            .def(py::init<double, double, double, double, const std::string &>())
            .def_readwrite("S0", &Derivative::S0)
            .def_readwrite("strike", &Derivative::strike)
            .def_readwrite("timeToMaturity", &Derivative::timeToMaturity)
            .def_readwrite("position", &Derivative::position)
            .def_readwrite("underlyingId", &Derivative::underlyingId)
            .def("payoff", &Derivative::payoff)
            .def("price", &Derivative::price);

    py::class_<EUCall, Derivative>(m, "EUCall")
            .def(py::init<double, double, double, double, const std::string &>())
            .def("payoff", &EUCall::payoff)
            .def("price", &EUCall::price);

    py::class_<EUPut, Derivative>(m, "EUPut")
            .def(py::init<double, double, double, double, const std::string &>())
            .def("payoff", &EUPut::payoff)
            .def("price", &EUPut::price);

    py::class_<CFD, Derivative>(m, "CFD")
            .def(py::init<double, double, double, double, const std::string &>())
            .def("payoff", &CFD::payoff)
            .def("price", &CFD::price);

    py::enum_<PricingMethod>(m, "PricingMethod")
            .value("MTE_CARLO", MTE_CARLO)
            .value("BLACK_SCHOLES", BLACK_SCHOLES)
            .value("BINOMIAL", BINOMIAL)
            .export_values();
}
