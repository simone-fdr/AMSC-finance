#ifndef BLACK_SCHOLES_HPP
#define BLACK_SCHOLES_HPP

double BlackScholesCall( double spot, double strike, double r, double d, double vol, double expiry);

double BlackScholesPut( double spot, double strike, double r, double d, double vol, double expiry);

double BlackScholesDigitalCall(double spot, double strike, double r, double d, double vol, double expiry);

double BlackScholesCallVega( double spot, double strike, double r, double d, double vol, double expiry);

#endif