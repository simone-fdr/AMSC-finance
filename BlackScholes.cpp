#include "BlackScholes.hpp"

double BlackScholesCall( double spot, double strike, double r, double d, double vol, double expiry) {
    double standardDeviation = vol*std::sqrt(expiry);
    double moneyness = std::log(spot/strike);
    double d1 = (moneyness + (r-d)*expiry + 0.5* standardDeviation*standardDeviation)/standardDeviation;
    double d2 = d1- standardDeviation;
    return spot*std::exp(-d*expiry) * cumulativeNormal(d1) - strike*std::exp(-r*expiry)*cumulativeNormal(d2);
}

double BlackScholesCallVega( double spot, double strike, double r, double d, double vol, double expiry) {
    double standardDeviation = vol*std::sqrt(expiry);
    double moneyness = std::log(spot/strike);
    double d1 = (moneyness + (r-d)*expiry + 0.5* standardDeviation*standardDeviation)/standardDeviation;
    return spot*std::exp(-d*expiry) * std::sqrt(expiry)*normalDensity(d1);
}

double BlackScholesPut( double spot, double strike, double r, double d, double vol, double expiry) {
    double standardDeviation = vol*std::sqrt(expiry);
    double moneyness = std::log(spot/strike);
    double d1 = (moneyness + (r-d)*expiry + 0.5* standardDeviation*standardDeviation)/standardDeviation;
    double d2 = d1- standardDeviation;
    return strike*std::exp(-r*expiry)*(1.0-cumulativeNormal(d2)) - spot*std::exp(-d*expiry) * (1-cumulativeNormal(d1));
}

double BlackScholesPutVega( double spot, double strike, double r, double d, double vol, double expiry) {
    double standardDeviation = vol*std::sqrt(expiry);
    double moneyness = std::log(spot/strike);
    double d1 = (moneyness + (r-d)*expiry + 0.5* standardDeviation*standardDeviation)/standardDeviation;
    return strike*std::exp(-d*expiry) * std::sqrt(expiry)*normalDensity(d1);
}

double BlackScholesDigitalCall( double spot, double strike, double r, double d, double vol, double expiry) {
    double standardDeviation = vol*std::sqrt(expiry);
    double moneyness = std::log(spot/strike);
    double d2 =(moneyness + (r-d)*expiry - 0.5* standardDeviation*standardDeviation)/standardDeviation;
    return std::exp(-r*expiry)*cumulativeNormal(d2);
}

double BlackScholesDigitalPut( double spot, double strike, double r, double d, double vol, double expiry) {
    double standardDeviation = vol*std::sqrt(expiry);
    double moneyness = std::log(spot/strike);
    double d2 =( moneyness + (r-d)*expiry - 0.5* standardDeviation*standardDeviation)/standardDeviation;
    return std::exp(-r*expiry)*(1.0-cumulativeNormal(d2));
}