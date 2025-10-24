#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "engine/products/Derivative.h"
#include "engine/utils/Greeks.h"

namespace py = pybind11;

inline int DEFAULT_NB_STEPS = 100; // TODO : Convert me into an enum
inline int DEFAULT_SEED = 123456789; // TODO : Convert me into an enum

class Model {
public:
    int steps = DEFAULT_NB_STEPS; // steps = n° of Monte-Carlo simulation, or n° of Binomial-steps
    int seed = DEFAULT_SEED;

    Model(int steps, int seed)
        : steps(steps),
          seed(seed) {
    }

    explicit Model(int steps)
        : steps(steps) {
    }

    Model() = default;

    virtual ~Model() = default;

    virtual py::array_t<double> simulatePaths(double S0, double param1, double param2) = 0;

    virtual double priceEUCall(double S0, double K, double T, double r, double sigma) = 0;

    double priceEUPut(double S0, double K, double T, double r, double sigma);

    /**
     *
     * @param greek
     * @param S0
     * @param K
     * @param T
     * @param r
     * @param sigma
     * @return
     * @note In the future, this method will have another argument, which is an enum corresponding to the option type,
     *       to get greeks of exotic opts. The same will apply to price methods, and the protected greeks methods.
     *       Or one will have to think of an exotic framework.
     * @todo In the future, this method will have another argument, which is an enum corresponding to the option type,
     *       to get greeks of exotic opts. The same will apply to price methods, and the protected greeks methods.
     *       Or one will have to think of an exotic framework.
     */
    virtual py::array_t<double> computeGreek(Greeks greek, double S0, double K, double T, double r, double sigma) = 0;

protected:
    /**
     *
     * @param S0
     * @param K
     * @param T
     * @param r
     * @param sigma
     * @return the delta of a EUCall and of a EUPut
     */
    virtual py::array_t<double> delta(double S0, double K, double T, double r, double sigma) = 0;

    virtual py::array_t<double> gamma(double S0, double K, double T, double r, double sigma) = 0;

    virtual py::array_t<double> theta(double S0, double K, double T, double r, double sigma) = 0;

    virtual py::array_t<double> vega(double S0, double K, double T, double r, double sigma) = 0;

    virtual py::array_t<double> rho(double S0, double K, double T, double r, double sigma) = 0;
};

#endif //MODEL_H
