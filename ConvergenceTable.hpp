#ifndef CONVERGENCE_TABLE_HPP
#define CONVERGENCE_TABLE_HPP

#include "Statistic.hpp"
#include "Wrapper.hpp"
class ConvergenceTable : public StatisticMC {
    public:
    // Constructor that sets the inner value
    ConvergenceTable(const Wrapper<StatisticMC>& inner_);

    // Clone constructor
    virtual StatisticMC* clone() const;

    //! @param result added to the statistic
    virtual void dumpOneResult(double result);

    //! @returns the results accumulated until this function call
    virtual std::vector<std::vector<double>> getResultsSoFar() const;

    //! @returns the most significant result accumulated untile this function call
    virtual double getResultSoFar() const;

    private:
    // Statistic from which the table is constructed
    Wrapper<StatisticMC> inner;
    // Table with the results accumulated
    std::vector<std::vector<double>> resultsSoFar;
    // Point where to stop
    unsigned long stoppingPoint;
    // Containst the number of paths done so far
    unsigned long pathsDone;
};

#endif