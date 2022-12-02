#ifndef SIMPLEMC_H
#define SIMPLEMC_H
#include <PayOff1.h>
    double SimpleMonteCarlo(const PayOff& thePayOff, double Expiry, double Spot,
                            double Vol, double r, unsigned long NumberOfPaths);
#endif