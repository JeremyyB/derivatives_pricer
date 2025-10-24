#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "engine/models/BlackScholes.h"
#include "engine/models/MonteCarlo.h"
#include "engine/models/Binomial.h"

#include "engine/products/cfd.h"
#include "engine/products/Derivative.h"
#include "engine/products/eu_call.h"
#include "engine/products/eu_put.h"
#include "engine/products/straddle.h"
#include "engine/products/strangle.h"
#include "engine/utils/Greeks.h"

namespace py = pybind11;

// Trampoline class for Derivative  
class PyDerivative : public Derivative {
public:
    using Derivative::Derivative; // inherit constructors

    double payoff(double S1) override {
        PYBIND11_OVERRIDE_PURE(double, Derivative, payoff, S1);
    }

    double price(double vol, double riskfree_rate, const std::shared_ptr<PricingParams> &methodsParam) override {
        PYBIND11_OVERRIDE_PURE(double, Derivative, price, vol, riskfree_rate, methodsParam);
    }

    py::array_t<double> greeks(double vol, double riskfree_rate,
                               const std::shared_ptr<PricingParams> &methodsParam) override {
        PYBIND11_OVERRIDE_PURE(py::array_t<double>, Derivative, greeks, vol, riskfree_rate, methodsParam);
    }
};

// Trampoline class for Model
class PyModel : public Model {
public:
    using Model::Model; // inherit constructors

    py::array_t<double> simulatePaths(double S0, double param1, double param2) override {
        PYBIND11_OVERRIDE_PURE(
            py::array_t<double>, // As before, return type  
            Model, // Parent class
            simulatePaths, // Name of function in C++
            S0, param1, param2 // args
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
    m.doc() = "C++ derivatives pricing library with Black-Scholes, Monte Carlo and Binomial Tree methods";
    // Module docstring

    /**
     *  Products
     */
    py::class_<Derivative, PyDerivative /* trampoline */>(m, "Derivative",
                                                          "Abstract base class for derivative products")
            .def(py::init<double, double, double, double, const std::string &>(),
                 "Constructor",
                 py::arg("S0"), py::arg("strike"), py::arg("timeToMaturity"),
                 py::arg("position"), py::arg("underlyingId"))
            .def_readwrite("S0", &Derivative::S0, "Initial underlying price")
            .def_readwrite("strike", &Derivative::strike, "Strike price")
            .def_readwrite("timeToMaturity", &Derivative::timeToMaturity, "Time to maturity in years")
            .def_readwrite("position", &Derivative::position, "Position size (+1 for long, -1 for short)")
            .def_readwrite("underlyingId", &Derivative::underlyingId, "Underlying asset identifier")
            .def("payoff", &Derivative::payoff, "Calculate payoff", py::arg("S1"))
            .def("price", &Derivative::price, "Price the derivative",
                 py::arg("vol"), py::arg("riskfree_rate"), py::arg("methodsParam"))
            .def("greeks", &Derivative::greeks, "Greeks' model computation",
                 py::arg("vol"), py::arg("riskfree_rate"), py::arg("methodsParam"));

    py::class_<EUCall, Derivative>(m, "EUCall", "European Call Option")
            .def(py::init<double, double, double, double, const std::string &>(),
                 "Constructor",
                 py::arg("S0"), py::arg("strike"), py::arg("timeToMaturity"),
                 py::arg("position"), py::arg("underlyingId"))
            .def("payoff", &EUCall::payoff, "Calculate payoff")
            .def("price", &EUCall::price, "Price the option")
            .def("greeks", &Derivative::greeks, "Greeks' model computation",
                 py::arg("vol"), py::arg("riskfree_rate"), py::arg("methodsParam"));;

    py::class_<EUPut, Derivative>(m, "EUPut", "European Put Option")
            .def(py::init<double, double, double, double, const std::string &>(),
                 "Constructor",
                 py::arg("S0"), py::arg("strike"), py::arg("timeToMaturity"),
                 py::arg("position"), py::arg("underlyingId"))
            .def("payoff", &EUPut::payoff, "Calculate payoff")
            .def("price", &EUPut::price, "Price the option")
            .def("greeks", &Derivative::greeks, "Greeks' model computation",
                 py::arg("vol"), py::arg("riskfree_rate"), py::arg("methodsParam"));;

    py::class_<CFD, Derivative>(m, "CFD", "Contract For Difference")
            .def(py::init<double, double, double, const std::string &>(),
                 "Constructor",
                 py::arg("S0"), py::arg("timeToMaturity"),
                 py::arg("position"), py::arg("underlyingId"))
            .def("payoff", &CFD::payoff, "Calculate payoff")
            .def("price", &CFD::price, "Price the CFD")
            .def("greeks", &Derivative::greeks, "Greeks' model computation",
                 py::arg("vol"), py::arg("riskfree_rate"), py::arg("methodsParam"));;

    py::class_<Strangle, Derivative>(m, "Strangle", "Strangle Option Strategy")
            .def(py::init<double, double, double, const std::string &, double, double>(),
                 "Constructor",
                 py::arg("S0"), py::arg("timeToMaturity"), py::arg("position"),
                 py::arg("underlyingId"), py::arg("kput"), py::arg("kcall"))
            .def("payoff", &Strangle::payoff, "Calculate payoff")
            .def("price", &Strangle::price, "Price the strategy")
            .def("greeks", &Derivative::greeks, "Greeks' model computation",
                 py::arg("vol"), py::arg("riskfree_rate"), py::arg("methodsParam"));;

    py::class_<Straddle, Strangle>(m, "Straddle", "Straddle Option Strategy")
            .def(py::init<double, double, double, double, const std::string &>(),
                 "Constructor",
                 py::arg("S0"), py::arg("strike"), py::arg("timeToMaturity"),
                 py::arg("position"), py::arg("underlyingId"))
            .def("payoff", &Straddle::payoff, "Calculate payoff")
            .def("price", &Straddle::price, "Price the strategy")
            .def("greeks", &Derivative::greeks, "Greeks' model computation",
                 py::arg("vol"), py::arg("riskfree_rate"), py::arg("methodsParam"));;

    /**
     *  Models
     */
    py::class_<Model, PyModel>(m, "Model", "Abstract base class for pricing models")
            .def(py::init<int, int>(),
                 "Constructor",
                 py::arg("steps") = DEFAULT_NB_STEPS, py::arg("seed") = DEFAULT_SEED)
            .def(py::init<int>(), py::arg("steps"))
            .def(py::init<>())
            .def_readwrite("steps", &Model::steps, "Number of time steps")
            .def_readwrite("seed", &Model::seed, "Random seed")
            .def("simulatePaths", &Model::simulatePaths, "Simulate price paths")
            .def("priceEUCall", &Model::priceEUCall, "Price European Call option")
            .def("priceEUPut", &Model::priceEUPut, "Price European Put option");

    py::class_<BlackScholes, Model>(m, "BlackScholes", "Black-Scholes Model")
            .def(py::init<>(), "Constructor")
            .def("simulatePaths", &BlackScholes::simulatePaths, "Simulate price paths")
            .def("priceEUCall", &BlackScholes::priceEUCall, "Price European Call option");

    py::class_<MonteCarlo, Model>(m, "MonteCarlo", "Monte Carlo Simulation Model")
            .def(py::init<int, int, int>(),
                 "Constructor",
                 py::arg("steps") = DEFAULT_NB_STEPS, py::arg("simulations"),
                 py::arg("seed") = DEFAULT_SEED)
            .def(py::init<int, int>(), py::arg("steps"), py::arg("simulations"))
            .def("simulatePaths", &MonteCarlo::simulatePaths, "Simulate price paths")
            .def("priceEUCall", &MonteCarlo::priceEUCall, "Price European Call option");

    py::class_<Binomial, Model>(m, "Binomial", "Binomial Tree Model")
            .def(py::init<int, double, double>(),
                 "Constructor",
                 py::arg("steps") = DEFAULT_NB_STEPS, py::arg("u"),
                 py::arg("d"))
            .def("simulatePaths", &Binomial::simulatePaths, "Simulate price paths")
            .def("priceEUCall", &Binomial::priceEUCall, "Price European Call option");

    /**
     * Greeks
     */

    py::enum_<Greeks>(m, "Greeks", "Available greeks")
            .value("DELTA", DELTA, "Price derivative")
            .value("GAMMA", GAMMA, "Price second derivative")
            .value("VEGA", VEGA, "Vol derivative")
            .value("THETA", THETA, "Time derivative")
            .value("RHO", RHO, "Risk-free rate derivative")
            .export_values();

    /**
    *  Pricing Params, Pricing Methods
    */
    py::enum_<PricingMethod>(m, "PricingMethod", "Available pricing methods")
            .value("MTE_CARLO", MTE_CARLO, "Monte Carlo simulation")
            .value("BLACK_SCHOLES", BLACK_SCHOLES, "Black-Scholes closed form")
            .value("BINOMIAL", BINOMIAL, "Binomial tree")
            .export_values();

    py::class_<PricingParams, std::shared_ptr<PricingParams> >(m, "PricingParams", "Base class for pricing parameters");

    py::class_<MonteCarloParams, PricingParams, std::shared_ptr<MonteCarloParams> >(
                m, "MonteCarloParams", "Monte Carlo simulation parameters")
            .def(py::init<int, int, int>(),
                 "Constructor",
                 py::arg("simulations"), py::arg("seed") = DEFAULT_SEED,
                 py::arg("steps") = DEFAULT_NB_STEPS)
            .def_readwrite("simulations", &MonteCarloParams::simulations, "Number of simulations")
            .def_readwrite("seed", &MonteCarloParams::seed, "Random seed")
            .def_readwrite("steps", &MonteCarloParams::steps, "Number of time steps");

    py::class_<BinomialParams, PricingParams, std::shared_ptr<BinomialParams> >(
                m, "BinomialParams", "Binomial tree parameters")
            .def(py::init<int, double, double>(),
                 "Constructor",
                 py::arg("steps") = DEFAULT_NB_STEPS,
                 py::arg("u") = 1.5, py::arg("d") = .5)
            .def_readwrite("steps", &BinomialParams::steps, "Number of time steps")
            .def_readwrite("u", &BinomialParams::u, "Up factor")
            .def_readwrite("d", &BinomialParams::d, "Down factor");

    py::class_<BlackScholesParams, PricingParams, std::shared_ptr<BlackScholesParams> >(
                m, "BlackScholesParams", "Black-Scholes parameters")
            .def(py::init<>(), "Constructor");
}
