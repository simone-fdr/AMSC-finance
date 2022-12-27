#ifndef EXOTIC_ENGINE_HPP
#define EXOTIC_ENGINE_HPP

#include "Wrapper.hpp"
#include "Parameter.hpp"
#include "Path.hpp"
#include "Statistic.hpp"
#include "Random.hpp"
#include <vector>
#include <cmath>
#include <omp.h>

class ExoticEngine {
    public:
    ExoticEngine(const Wrapper<Path>& product_, const Parameter& r_);
    virtual void getOnePath(FinArray& spotValues)=0;
    void doSimulation(StatisticMC& gatherer, unsigned long numberOfPaths);
    virtual ~ExoticEngine(){}
    double doOnePath(const FinArray& spotValues) const;
    private:
    Wrapper<Path> product;
    Parameter r;
    FinArray discounts;
    mutable std::vector<CashFlow> vectCashFlows;
};

class ExoticBSEngine : public ExoticEngine
{
    public:
    ExoticBSEngine(const Wrapper<Path>& product_, const Parameter& r_, const Parameter& d_,
                const Parameter& vol_, const Wrapper<RandomBase>& generator_, double spot_);
    virtual void getOnePath(FinArray& spotValues);
    virtual ~ExoticBSEngine(){}
    private:
    Wrapper<RandomBase> generator;
    FinArray drifts;
    FinArray standardDeviations;
    double logSpot;
    unsigned long numberOfTimes;
    FinArray variates;
};

#endif