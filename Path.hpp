#ifndef PATH_HPP
#define PATH_HPP

#include "Array.hpp"
#include "PayOff.hpp"
#include <vector>

class CashFlow {
    public:
    double amount;
    unsigned long timeIndex;
    CashFlow(unsigned long timeIndex_=0UL, double amount_=0.0) : timeIndex(timeIndex_), amount(amount_){};
};

class Path {
    public:
    Path(const FinArray& lookAtTimes);
    const FinArray& getLookAtTimes() const;
    virtual unsigned long maxNumberOfCashFlows() const=0;
    virtual FinArray possibleCashFlowTimes() const=0;
    virtual unsigned long cashFlows(const FinArray& spotValues, std::vector<CashFlow>& GeneratedFlows) const=0;
    virtual Path* clone() const=0;
    virtual ~Path() = default;
    private:
    FinArray lookAtTimes;
};

class PathAsian : public Path {
    public:
    PathAsian(const FinArray& lookAtTimes_, double deliveryTime_, const PayOffBridge& payOff_);
    virtual unsigned long maxNumberOfCashFlows() const;
    virtual FinArray possibleCashFlowTimes() const;
    virtual unsigned long cashFlows(const FinArray& spotValues, std::vector<CashFlow>& generatedFlows) const;
    virtual ~PathAsian() = default;
    virtual Path* clone() const;
    private:
    double deliveryTime;
    PayOffBridge payOff;
    unsigned long numberOfTimes;
};

#endif