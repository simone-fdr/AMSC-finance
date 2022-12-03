#include "Random.hpp"
#include "SimpleMC.hpp"
#include <iostream>
#include <cmath>

void simpleMonteCarlo(const VanillaOption& option, double spot, const Parameter& vol,
                      const Parameter& r, unsigned long numberOfPaths, StatisticMC& gatherer){
    double expiry = option.getExpiry();
    double variance = vol.integralSquare(0, expiry);
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5*variance;
    double movedSpot = spot*std::exp(r.integral(0, expiry) + itoCorrection);
    double thisSpot;
    double discounting = std::exp(-r.integral(0, expiry));
    double sum=0;
    for (unsigned long i=0; i < numberOfPaths; i++){
        double gaussian = getOneGaussianByBoxMuller();
        thisSpot = movedSpot*std::exp(rootVariance*gaussian);
        double payOff = option.payOff(thisSpot);
        gatherer.dumpOneResult(payOff*discounting);
    }
    return;
}