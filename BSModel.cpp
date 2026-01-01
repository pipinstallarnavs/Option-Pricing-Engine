#include "BSModel.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <iostream>

// Constructor Implementation
BSModel::BSModel(double S0, double K, double r, double sigma, double T)
    : S0(S0), K(K), r(r), sigma(sigma), T(T) {}

// Monte Carlo Pricing Implementation
double BSModel::priceOption(int num_simulations, OptionType type) const {
    
    // 1. Setup Random Number Generation
    // Using std::random_device to seed the Mersenne Twister
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Standard Normal Distribution Z ~ N(0, 1)
    std::normal_distribution<> d(0.0, 1.0);

    // 2. Pre-calculate Drift and Diffusion components
    // This avoids recalculating constants inside the loop (Optimization)
    double drift = (r - 0.5 * sigma * sigma) * T;
    double diffusion = sigma * std::sqrt(T);

    double payoff_sum = 0.0;

    // 3. Run Simulation Loop
    for (int i = 0; i < num_simulations; ++i) {
        // Generate random Z
        double Z = d(gen);

        // Calculate Asset Price at Maturity (ST)
        double ST = S0 * std::exp(drift + diffusion * Z);

        // Calculate Payoff based on Option Type
        double payoff = 0.0;
        if (type == OptionType::Call) {
            payoff = std::max(0.0, ST - K);
        } else { // Put
            payoff = std::max(0.0, K - ST);
        }

        payoff_sum += payoff;
    }

    // 4. Calculate Average and Discount back to Present Value
    double average_payoff = payoff_sum / static_cast<double>(num_simulations);
    double discount_factor = std::exp(-r * T);

    return discount_factor * average_payoff;
}