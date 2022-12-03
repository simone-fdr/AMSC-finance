#include "Random.hpp"
#include "SimpleMC.hpp"
#include <iostream>
#include <cmath>

void simpleMonteCarlo(const VanillaOption& option, double spot, const Parameter& vol,
                      const Parameter& r, unsigned long numberOfPaths, StatisticMC& gatherer, RandomBase& generator){

    generator.resetDimensionality(1);

    double expiry = option.getExpiry();
    double variance = vol.integralSquare(0, expiry);
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5*variance;
    double movedSpot = spot*std::exp(r.integral(0, expiry) + itoCorrection);
    double thisSpot;
    double discounting = std::exp(-r.integral(0, expiry));

    FinArray variates(1);

    for (unsigned long i=0; i < numberOfPaths; i++){
        generator.getGaussians(variates);
        thisSpot = movedSpot*std::exp(rootVariance*variates[0]);
        double payOff = option.payOff(thisSpot);
        gatherer.dumpOneResult(payOff*discounting);
    }

    return;
}