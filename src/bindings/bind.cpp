#include <iostream>
#include <pybind11/pybind11.h>

#include "engine/models/BlackScholes.h"
#include "engine/products/cfd.h"
#include "engine/products/Derivative.h"
#include "engine/products/eu_call.h"
#include "engine/products/eu_put.h"
#include "engine/products/straddle.h"
#include "engine/products/strangle.h"

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

// Trampoline class for Model
class PyModel : public Model {
public:
    using Model::Model; // inherit constructors

    std::vector<double> simulatePaths() override {
        PYBIND11_OVERRIDE_PURE(
            std::vector<double>, // As before, return type
            Model, // Parent class
            simulatePaths // Name of function in C++
        );
    }

    double priceEUCall(double S0, double K, double T, double r, double sigma) override {
        PYBIND11_OVERRIDE(
            double,
            Model,
            priceEUCall,
            S0, K, T, r, sigma
        );
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
            .def(py::init<double, double, double, const std::string &>())
            .def("payoff", &CFD::payoff)
            .def("price", &CFD::price);

    py::class_<Strangle, Derivative>(m, "Strangle")
            .def(py::init<double, double, double, const std::string &, double, double>())
            .def("payoff", &Strangle::payoff)
            .def("price", &Strangle::price);

    py::class_<Straddle, Strangle>(m, "Straddle")
            .def(py::init<double, double, double, double, const std::string &>())
            .def("payoff", &Straddle::payoff)
            .def("price", &Straddle::price);

    py::enum_<PricingMethod>(m, "PricingMethod")
            .value("MTE_CARLO", MTE_CARLO)
            .value("BLACK_SCHOLES", BLACK_SCHOLES)
            .value("BINOMIAL", BINOMIAL)
            .export_values();

    py::class_<Model, PyModel /* Trampoline */>(m, "Model")
            .def(py::init<int, int>(), py::arg("steps") = DEFAULT_NB_STEPS, py::arg("seed") = DEFAULT_SEED)
            .def(py::init<int>(), py::arg("steps"))
            .def_readwrite("steps", &Model::steps)
            .def_readwrite("seed", &Model::seed)
            .def("simulatePaths", &Model::simulatePaths)
            .def("priceEUCall", &Model::priceEUCall)
            .def("priceEUPut", &Model::priceEUPut);

    py::class_<BlackScholes, Model>(m, "BlackScholes")
            .def(py::init<int, int>(), py::arg("steps") = DEFAULT_NB_STEPS, py::arg("seed") = DEFAULT_SEED)
            .def(py::init<int>(), py::arg("steps"))
            .def("simulatePaths", &BlackScholes::simulatePaths)
            .def("priceEUCall", &BlackScholes::priceEUCall);
}
