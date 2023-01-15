#ifndef ANTITHETIC_HPP
#define ANTITHETIC_HPP

#include "Random.hpp"
#include "Wrapper.hpp"

class AntiThetic : public RandomBase {
    public:
    //! @param innerGenerator is the generator that actual outputs the random number 
    AntiThetic(const Wrapper<RandomBase>& innerGenerator);

    // clone constructor
    virtual RandomBase* clone() const;

    //! @param variates the array to be filld with uniforms
    virtual void getUniforms(FinArray& variates);

    // Skips some random numbers in order to increase randomness
    //! @param numberOfPaths the number to be skipped
    virtual void skip(unsigned long numberOfPaths);

    //! @param seed to set in the innerGenerator
    virtual void setSeed(unsigned long seed);

    // Resizes the dimension
    //! @param newDimensionality dimension to set
    virtual void resetDimensionality(unsigned long newDimensionality);

    // Resets the number generation
    virtual void reset();
    private:
    // Actual random generator
    Wrapper<RandomBase> innerGenerator;
    
    //Boolean that checks wheter it has to generate or use antithetic
    bool oddEven;

    // Stores antithetic values
    FinArray nextVariates;
};

#endif