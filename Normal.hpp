#ifndef NORMAL_HPP
#define NORMAL_HPP

#include <cmath>
// probability density for a standard Gaussian distribution
double normalDensity(double x);

// standard normal cumulative distribution function
double cumulativeNormal(double x);

// the InverseCumulativeNormal function via the
// Beasley-Springer/Moro approximation
double inverseCumulativeNormal(double x);

const double oneOverRootTwoPi = 0.398942280401433;

#endif