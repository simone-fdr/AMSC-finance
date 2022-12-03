#ifndef ANTITHETIC_HPP
#define ANTITHETIC_HPP

#include "Random.hpp"
#include "Wrapper.hpp"

class AntiThetic : public RandomBase {
    public:
    AntiThetic(const Wrapper<RandomBase>& innerGenerator);
    virtual RandomBase* clone() const;
    virtual void getUniforms(FinArray& variates);
    virtual void skip(unsigned long numberOfPaths);
    virtual void setSeed(unsigned long seed);
    virtual void resetDimensionality(unsigned long newDimensionality);
    virtual void reset();
    private:
    Wrapper<RandomBase> innerGenerator;
    bool oddEven;
    FinArray nextVariates;
};

#endif