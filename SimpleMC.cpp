#include "Random.hpp"
#include "SimpleMC.hpp"
#include <iostream>
#include <cmath>
#include <chrono>

void generate(RandomBase& generator, FinArray& variates, double thisSpot, double movedSpot,
                         const VanillaOption& option, StatisticMC& gatherer, double discounting, double rootVariance){
    generator.getGaussians(variates);
    thisSpot = movedSpot*std::exp(rootVariance*variates[0]);
    double payOff = option.payOff(thisSpot);
    gatherer.dumpOneResult(payOff*discounting);
}


void monteCarlo(const VanillaOption& option, double spot, const Parameter& vol,
                      const Parameter& r, StatisticMC& gatherer, RandomBase& generator, Terminator& terminator){
    generator.resetDimensionality(1);
    double expiry = option.getExpiry();
    double variance = vol.integralSquare(0, expiry);
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5*variance;
    double movedSpot = spot*std::exp(r.integral(0, expiry) + itoCorrection);
    double thisSpot;
    double discounting = std::exp(-r.integral(0, expiry));

    FinArray variates(1);

    while(!terminator.isTerminated()){
        generate(generator, variates, thisSpot, movedSpot, option, gatherer, discounting, rootVariance);
    }
    return;
}