#ifndef PARK_MILLER_HPP
#define PARK_MILLER_HPP
#include "Random.hpp"

class ParkMiller {
    public:
    // Constructor
    //! @param seed to set
    ParkMiller(long seed = 1);
    //! @returns one integer between min() and max()
    long getOneRandomInteger();
    //! @param seed to set
    void setSeed(long seed);
    //! @returns max value of integer that can be generated
    static unsigned long max();
    //! @returns min value of integer that can be generated
    static unsigned long min();
    private:
    // seed of the random number generator
    long seed;
};

class RandomParkMiller : public RandomBase {
    public:
    //! @param dimenstionality of the numbers to generate
    //! @param seed used
    RandomParkMiller(unsigned long dimensionality, unsigned long seed=1);
    // Clone constructor
    virtual RandomBase* clone() const;
    //! @param variates array that will be filled with uniforms
    virtual void getUniforms(FinArray& variates);
    //! @param numberOfPaths to be skipped in the generation
    virtual void skip(unsigned long numberOfPaths);
    //! @param seed to be set
    virtual void setSeed(unsigned long seed);
    //! Resets the generation of numbers
    virtual void reset();
    //! @param newDimensionality to be set
    virtual void resetDimensionality(unsigned long newDimensionality);
    private:
    // generator of numbers
    ParkMiller innerGenerator;
    // seed of the generator
    unsigned long initialSeed;
    // value used to make ParkMiller a U(0,1) generator
    double reciprocal;
};

#endif