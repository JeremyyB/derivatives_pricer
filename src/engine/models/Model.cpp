#include "Model.h"

double Model::priceEUPut(double S0, double K, double T, double r, double sigma) {
    return this->priceEUCall(S0, K, T, r, sigma) - S0 + K * exp(-r * T);
    // Using Call-Put Parity : C - P = S - Ke^-r(T)
}

double Model::priceEUCall(double S0, double K, double T, double r, double sigma) {
    throw std::runtime_error("priceEUCall must be implemented by derived class");
}

