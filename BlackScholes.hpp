#ifndef BLACK_SCHOLES_HPP
#define BLACK_SCHOLES_HPP
#include "Normal.hpp"
#include <cmath>

// Returns the theoretical value of a call in a Black-Scholes model
//! @param spot of the option
//! @param strike of the option
//! @param r risk-free market return
//! @param d dividend yields
//! @param vol volatility of the market
//! @param expiry date of the option
double BlackScholesCall( double spot, double strike, double r, double d, double vol, double expiry);

// Returns the theoretical value of a put in a Black-Scholes model
//! @param spot of the option
//! @param strike of the option
//! @param r risk-free market return
//! @param d dividend yields
//! @param vol volatility of the market
//! @param expiry date of the option
double BlackScholesPut( double spot, double strike, double r, double d, double vol, double expiry);

// Returns the mathematical derivative of a call in a Black-Scholes model
//! @param spot of the option
//! @param strike of the option
//! @param r risk-free market return
//! @param d dividend yields
//! @param vol volatility of the market
//! @param expiry date of the option
double BlackScholesCallVega( double spot, double strike, double r, double d, double vol, double expiry);

// Returns the tmathematical derivative of a of a put in a Black-Scholes model
//! @param spot of the option
//! @param strike of the option
//! @param r risk-free market return
//! @param d dividend yields
//! @param vol volatility of the market
//! @param expiry date of the option
double BlackScholesPutVega( double spot, double strike, double r, double d, double vol, double expiry);

// Returns the boolean result of a digital call in a Black-Scholes model
//! @param spot of the option
//! @param strike of the option
//! @param r risk-free market return
//! @param d dividend yields
//! @param vol volatility of the market
//! @param expiry date of the option
double BlackScholesDigitalCall(double spot, double strike, double r, double d, double vol, double expiry);

#endif