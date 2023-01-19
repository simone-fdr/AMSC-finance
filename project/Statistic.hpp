#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <vector>
#include <memory>
#include "Wrapper.hpp"

// Abstract class that represent a statistic
class StatisticMC {
    public:
    StatisticMC() = default;
    //! @param result added to the statistic
    virtual void dumpOneResult(double result)=0;
    //! @return the results accumulated until this function call
    virtual std::vector<std::vector<double>> getResultsSoFar() const=0;
    //! @returns the most significant result accumulated untile this function call
    virtual double getResultSoFar() const=0;
    // Clears the history of data accumulated
    virtual void clear() = 0;
    // Clone constructor
    virtual StatisticMC* clone() const=0;
    // Deconstructor
    virtual ~StatisticMC() = default;
    private:
};

class StatisticMean : public StatisticMC {
    public:
    StatisticMean();
    //! @param result summed to the statistic
    virtual void dumpOneResult(double result);
    //! @return the mean of results accumulated until this function call
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    //! @returns the mean result accumulated untile this function call
    virtual double getResultSoFar() const;
    // Clears the history of data accumulated
    virtual void clear();
    // Clone constructor
    virtual StatisticMC* clone() const;
    private:
    // Sum of the results accumulated
    double sum;
    // How many results have been accumulated
    unsigned long pathsDone;
};

class StatisticMoment : public StatisticMC {
    public:
    StatisticMoment();
    //! @param result summed to the statistic
    virtual void dumpOneResult(double result);
    //! @return the first four moments of results accumulated until this function call
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    //! @returns the second moment of results accumulated untile this function call
    virtual double getResultSoFar() const;
    // Clears the history of data accumulated
    virtual void clear();
    // Clone constructor
    virtual StatisticMC* clone() const;
    private:
    // Sum used for first moment
    double sum;
    // Sum used for second moment
    double sum2;
    // Sum used for third moment
    double sum3;
    // Sum used for fourth moment
    double sum4;
    // How many results have been accumulated
    unsigned long pathsDone;
};

class StatisticVaR : public StatisticMC {
    public:
    StatisticVaR();
    //! @param result summed to the statistic and updates worst
    virtual void dumpOneResult(double result);
    //! @return the Value at Risk of results accumulated until this function call
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    //! @returns the Value at Risk of results accumulated untile this function call
    virtual double getResultSoFar() const;
    // Clears the history of data accumulated
    virtual void clear();
    // Clone constructor
    virtual StatisticMC* clone() const;
    private:
    // Sum of the result
    double sum;
    // Worst result met
    double worst;
    // How many results have been accumulated
    unsigned long pathsDone;
};

// Is a merge of different statistics
class Statistics : public StatisticMC {
    public:
    // Constuctor
    Statistics();
    // Add one result to all the statistics
    virtual void dumpOneResult(double result);
    //! @returns all the statistics accumulated so far
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    //! @returns the most significant statistic 
    virtual double getResultSoFar() const;
    // Clears the history of data accumulated
    virtual void clear();
    // Clone constructor
    virtual StatisticMC* clone() const;
    //! @param statistic added to the vector
    void addStatistic(StatisticMC& statistic);
    private:
    // Statistics stored, use of Wrapper to enable polymorphism
    std::vector<Wrapper<StatisticMC>> statistics;
};

#endif