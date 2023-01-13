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
    // Constructor
    //! @param product_ path to analyze
    //! @param r risk-free market
    ExoticEngine(const Wrapper<Path>& product_, const Parameter& r_);
    //! @param spotValues with which initializes the path
    virtual void getOnePath(FinArray& spotValues)=0;
    // Does a simulation
    //! @param numberOfPaths is the number of simulations done 
    //! @param gathere is where the values are stored
    void doSimulation(StatisticMC& gatherer, unsigned long numberOfPaths);
    // Deconstructor
    virtual ~ExoticEngine() = default;
    // Simulation of one path
    //! @param spotValues used to simulate
    double doOnePath(const FinArray& spotValues) const;
    private:
    // Path used for simulation
    Wrapper<Path> product;
    // Risk-free market product
    Parameter r;
    // Discounts over time
    FinArray discounts;
    // Vector of cashflows generated
    mutable std::vector<CashFlow> vectCashFlows;
};

class ExoticBSEngine : public ExoticEngine
{
    public:
    // Constructor
    //! @param product_ path followed
    //! @param r_ risk-free market
    //! @param d_ dividen yields
    //! @param vol_ volatility of market
    //! @param generator_ of random numbers
    //! @param spot_ of the product
    ExoticBSEngine(const Wrapper<Path>& product_, const Parameter& r_, const Parameter& d_,
                const Parameter& vol_, const Wrapper<RandomBase>& generator_, double spot_);
    //! @param spotValues with which the path is generated
    virtual void getOnePath(FinArray& spotValues);
    // Deconstructor
    virtual ~ExoticBSEngine() = default;
    private:
    // generator of random numbers
    Wrapper<RandomBase> generator;
    // Intermediate value used for calculations
    FinArray drifts;
    // Standard deviation of the product
    FinArray standardDeviations;
    // Spot in logaritmic scale
    double logSpot;
    // Number of times used for simulation
    unsigned long numberOfTimes;
    // Array to store random numbers
    FinArray variates;
};

#endif