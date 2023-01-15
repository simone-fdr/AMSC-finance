#include "AntiThetic.hpp"

AntiThetic::AntiThetic(const Wrapper<RandomBase>& innerGenerator_): RandomBase(*innerGenerator_), innerGenerator(innerGenerator_) {
    innerGenerator->reset();
    oddEven = true;
    nextVariates.resize(getDimensionality());
}

RandomBase* AntiThetic::clone() const {
    return new AntiThetic(*this);
}

void AntiThetic::getUniforms(FinArray& variates) {
    if (oddEven) {
        innerGenerator->getUniforms(variates);
        for (unsigned long i =0; i < getDimensionality(); i++)
            nextVariates[i] = 1.0-variates[i];
        oddEven = false;
    } else {
        variates = nextVariates;
        oddEven = true;
    }
}

void AntiThetic::setSeed(unsigned long seed) {
    innerGenerator->setSeed(seed);
    oddEven = true;
}

void AntiThetic::skip(unsigned long numberOfPaths) {
    if (numberOfPaths ==0)
        return;
    if (oddEven) {
        oddEven = false;
        numberOfPaths--;
    }
    innerGenerator->skip(numberOfPaths / 2);
    if (numberOfPaths % 2) {
        FinArray tmp(getDimensionality());
        getUniforms(tmp);
    }
}

void AntiThetic::resetDimensionality(unsigned long newDimensionality) {
    RandomBase::resetDimensionality(newDimensionality);
    nextVariates.resize(newDimensionality);
    innerGenerator->resetDimensionality(newDimensionality);
}

void AntiThetic::reset() {
    innerGenerator->reset();
    oddEven =true;
}