#ifndef CONVERGENCE_TABLE_HPP
#define CONVERGENCE_TABLE_HPP

#include "Statistic.hpp"
#include "Wrapper.hpp"
class ConvergenceTable : public StatisticMC {
    public:
    ConvergenceTable(const Wrapper<StatisticMC>& inner_);
    virtual StatisticMC* clone() const;
    virtual void dumpOneResult(double result);
    virtual std::vector<std::vector<double>> getResultsSoFar() const;
    private:
    Wrapper<StatisticMC> inner;
    std::vector<std::vector<double>> resultsSoFar;
    unsigned long stoppingPoint;
    unsigned long pathsDone;
};

#endif