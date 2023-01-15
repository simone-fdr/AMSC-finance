#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "Array.hpp"
#include "Normal.hpp"
#include <cstdlib>
#include <cmath>

class RandomBase {
    public:
    // Constructor
    //! @param dimensionality_ numbers to generate
    RandomBase(unsigned long dimensionality_);
    //! @returns the dimenstionality of the random number generator
    inline unsigned long getDimensionality() const;
    // Clone constructor
    virtual RandomBase* clone() const=0;
    //! @param variates array filled with U(0,1) random numbers
    virtual void getUniforms(FinArray& variates)=0;
    //! @param numberOfPaths to be skipped
    virtual void skip(unsigned long numberOfPaths)=0;
    //! @param seed to be set
    virtual void setSeed(unsigned long seed) =0;
    // Resets the generation of numbers
    virtual void reset()=0;
    //! @param variates array filled with N(0,1) random numbers
    virtual void getGaussians(FinArray& variates);
    //! @param newDimensionality to be set
    virtual void resetDimensionality(unsigned long newDimensionality);
    private:
    // Dimension of number to be generated
    unsigned long dimensionality;
};

inline unsigned long RandomBase::getDimensionality() const {
    return dimensionality;
}

#endif
