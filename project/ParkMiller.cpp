#include "ParkMiller.hpp"

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

ParkMiller::ParkMiller(long seed_ ) : seed(seed_) {
    if (seed ==0)
        seed=1;
}

void ParkMiller::setSeed(long seed_) {
    seed=seed_;
    if (seed ==0)
        seed=1;
}

unsigned long ParkMiller::max() {
    return m-1;
}

unsigned long ParkMiller::min() {
    return 1;
}

long ParkMiller::getOneRandomInteger() {
    long k;
    k=seed/q;
    seed=a*(seed-k*q)-r*k;
    if (seed < 0)
        seed += m;
    return seed;
}

RandomParkMiller::RandomParkMiller(unsigned long dimensionality, unsigned long seed) : RandomBase(dimensionality), innerGenerator(seed), initialSeed(seed) {
    reciprocal = 1/(1.0+innerGenerator.max());
}

RandomBase* RandomParkMiller::clone() const {
    return new RandomParkMiller(*this);
}

void RandomParkMiller::getUniforms(FinArray& variates) {
    for (unsigned long j=0; j < getDimensionality(); j++)
        variates[j] = innerGenerator.getOneRandomInteger()*reciprocal;
}

void RandomParkMiller::skip(unsigned long numberOfPaths) {
    FinArray tmp(getDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        getUniforms(tmp);
}

void RandomParkMiller::setSeed(unsigned long seed) {
    initialSeed = seed;
    innerGenerator.setSeed(seed);
}

void RandomParkMiller::reset() {
    innerGenerator.setSeed(initialSeed);
}

void RandomParkMiller::resetDimensionality(unsigned long newDimensionality)
{
    RandomBase::resetDimensionality(newDimensionality);
    innerGenerator.setSeed(initialSeed);
}
