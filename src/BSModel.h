#pragma once
#include <vector>

enum class OptionType {
    Call,
    Put
};

class BSModel {
public:
    // Constructor requiring all market parameters
    BSModel(double S0, double K, double r, double sigma, double T);

    // Main pricing method using Monte Carlo Simulation
    double priceOption(int num_simulations, OptionType type) const;

private:
    // Market Parameters
    double S0;    // Initial Stock Price
    double K;     // Strike Price
    double r;     // Risk-free Rate
    double sigma; // Volatility
    double T;     // Time to Maturity (in years)

    // Helper for generating standard normal random variables
    // Note: We will keep RNG local to methods to support future threading
};