#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "Array.hpp"

class RandomBase {
    public:
    RandomBase(unsigned long dimensionality_);
    inline unsigned long getDimensionality() const;
    virtual RandomBase* clone() const=0;
    virtual void getUniforms(FinArray& variates)=0;
    virtual void skip(unsigned long numberOfPaths)=0;
    virtual void setSeed(unsigned long seed) =0;
    virtual void reset()=0;
    virtual void getGaussians(FinArray& variates);
    virtual void resetDimensionality(unsigned long newDimensionality);
    private:
    unsigned long dimensionality;
};

unsigned long RandomBase::getDimensionality() const {
    return dimensionality;
}

#endif
