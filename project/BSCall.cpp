#include "BSCall.hpp"

BSCall::BSCall(double r_, double d_, double t_, double spot_, double strike_) :
        r(r_), d(d_), t(t_), spot(spot_), strike(strike_) {}

double BSCall::price(double vol) const {
    return BlackScholesCall(spot, strike, r, d, vol, t);
}

double BSCall::vega(double vol) const {
    return BlackScholesCallVega(spot, strike, r, d, vol, t);
}

BSPut::BSPut(double r_, double d_, double t_, double spot_, double strike_) :
        r(r_), d(d_), t(t_), spot(spot_), strike(strike_) {}


double BSPut::price(double vol) const {
    return BlackScholesPut(spot, strike, r, d, vol, t);
}

double BSPut::vega(double vol) const {
    return BlackScholesPutVega(spot, strike, r, d, vol, t);
}