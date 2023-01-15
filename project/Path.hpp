#ifndef PATH_HPP
#define PATH_HPP

#include "Array.hpp"
#include "PayOff.hpp"
#include <vector>

// Data class that stores information
class CashFlow {
    public:
    // Number of cash flowes to calculate
    double amount;
    // Index of times for each cash flow
    unsigned long timeIndex;
    CashFlow(unsigned long timeIndex_=0UL, double amount_=0.0) : timeIndex(timeIndex_), amount(amount_){};
};

class Path {
    public:
    // Constructor
    //! @param lookAtTimes intervals of time
    Path(const FinArray& lookAtTimes);
    //! @returns the intervals of time
    const FinArray& getLookAtTimes() const;
    //! @returns the max number of cash flows that can be calculated
    virtual unsigned long maxNumberOfCashFlows() const=0;
    //! @returns the array with the cash flows
    virtual FinArray possibleCashFlowTimes() const=0;
    //! @param spotValues used to calculate cash flows
    //! @param GeneratedFlows array filled with cash flows
    //! @returns how many cash flows are calculated
    virtual unsigned long cashFlows(const FinArray& spotValues, std::vector<CashFlow>& GeneratedFlows) const=0;
    // Clone constructor
    virtual Path* clone() const=0;
    // Deconstructor
    virtual ~Path() = default;
    private:
    // array with intervals of times
    FinArray lookAtTimes;
};

class PathAsian : public Path {
    public:
    // Constructor
    //! @param lookAtTimes_ intervals of time
    //! @param deliveryTime_ moment in time for which the cash flow is calculated
    //! @param payOff_ used to calculate cash flows
    PathAsian(const FinArray& lookAtTimes_, double deliveryTime_, const PayOffBridge& payOff_);
    //! @returns the max number of cash flows that can be calculated
    virtual unsigned long maxNumberOfCashFlows() const;
    //! @returns the array with the cash flows
    virtual FinArray possibleCashFlowTimes() const;

    //! @param spotValues used to calculate cash flows
    //! @param GeneratedFlows array filled with cash flows
    //! @returns 1UL
    virtual unsigned long cashFlows(const FinArray& spotValues, std::vector<CashFlow>& generatedFlows) const;
    // Deconstructor
    virtual ~PathAsian() = default;
    // Clone constructor
    virtual Path* clone() const;
    private:
    // Time used to calculate cash flow
    double deliveryTime;
    // Payoff used to calculate cash flow
    PayOffBridge payOff;
    // How many spotValues are used to calculate cash flow
    unsigned long numberOfTimes;
};

#endif