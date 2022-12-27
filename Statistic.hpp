#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <vector>
#include <memory>
#include "Wrapper.hpp"

class StatisticMC {
    public:
    StatisticMC(){}
    virtual void dumpOneResult(double result)=0;
    virtual std::vector<std::vector<double>> getResultsSoFar() const=0;
    virtual double getResultSoFar() const=0;
    virtual StatisticMC* clone() const=0;
    virtual ~StatisticMC(){}
    private:
};

class StatisticMean : public StatisticMC {
    public:
    StatisticMean();
    virtual void dumpOneResult(double result);
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    virtual double getResultSoFar() const;
    virtual StatisticMC* clone() const;
    private:
    double sum;
    unsigned long pathsDone;
};

class StatisticMoment : public StatisticMC {
    public:
    StatisticMoment();
    virtual void dumpOneResult(double result);
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    virtual double getResultSoFar() const;
    virtual StatisticMC* clone() const;
    private:
    double sum;
    double sum2;
    double sum3;
    double sum4;
    unsigned long pathsDone;
};

class StatisticVaR : public StatisticMC {
    public:
    StatisticVaR();
    virtual void dumpOneResult(double result);
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    virtual double getResultSoFar() const;
    virtual StatisticMC* clone() const;
    private:
    double sum;
    double worst;
    unsigned long pathsDone;
};

class Statistics : public StatisticMC {
    public:
    Statistics();
    virtual void dumpOneResult(double result);
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    virtual double getResultSoFar() const;
    virtual StatisticMC* clone() const;
    void addStatistic(StatisticMC& statistic);
    private:
    std::vector<Wrapper<StatisticMC>> statistics;
};

#endif