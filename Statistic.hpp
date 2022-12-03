#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <vector>

class StatisticMC {
    public:
    StatisticMC(){}
    virtual void dumpOneResult(double result)=0;
    virtual std::vector<std::vector<double>> getResultsSoFar() const=0;
    virtual StatisticMC* clone() const=0;
    virtual ~StatisticMC(){}
    private:
};

class StatisticMean : public StatisticMC {
    public:
    StatisticMean();
    virtual void dumpOneResult(double result);
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    virtual StatisticMC* clone() const;
    private:
    double sum;
    unsigned long pathsDone;
};

#endif