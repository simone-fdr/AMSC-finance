#include "Random.hpp"

void RandomBase::getGaussians(FinArray& variates) {
    getUniforms(variates);
    for (unsigned long i=0; i < dimensionality; i++) {
    double x=variates[i];
    variates[i] = inverseCumulativeNormal(x);
    }
}

void RandomBase::resetDimensionality(unsigned long newDimensionality) {
    dimensionality = newDimensionality;
}

RandomBase::RandomBase(unsigned long dimensionality_) : dimensionality(dimensionality_) {}