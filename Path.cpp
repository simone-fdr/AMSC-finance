#include "Path.hpp"

Path::Path(const FinArray& lookAtTimes_) : lookAtTimes(lookAtTimes_) {}

const FinArray& Path::getLookAtTimes() const {
    return lookAtTimes;
}

PathAsian::PathAsian(const FinArray& lookAtTimes_, double deliveryTime_, const PayOffBridge& payOff_) :
Path(lookAtTimes_), deliveryTime(deliveryTime_), payOff(payOff_), numberOfTimes(lookAtTimes_.size()) {}

// Return 1 for simplicity
unsigned long PathAsian::maxNumberOfCashFlows() const {
    return 1UL;
}

// Since it only return 1 value, the only time is the expiry date
FinArray PathAsian::possibleCashFlowTimes() const {
    FinArray tmp(1UL);
    tmp[0] = deliveryTime;
    return tmp;
}

unsigned long PathAsian::cashFlows(const FinArray& spotValues, std::vector<CashFlow>& generatedFlows) const {
    double sum = spotValues.sum();
    double mean = sum/numberOfTimes;
    generatedFlows[0].timeIndex = 0UL;
    generatedFlows[0].amount = payOff(mean);
    return 1UL;
}

Path* PathAsian::clone() const {
    return new PathAsian(*this);
}