#ifndef PAYOFFBRIDGE_HPP
#define PAYOFFBRIDGE_HPP

#include "PayOff.hpp"

class PayOffBridge {
    public:
    PayOffBridge(const PayOffBridge& original);
    PayOffBridge(const PayOff& innerPayOff);
    inline double operator()(double spot) const;
    ~PayOffBridge();
    PayOffBridge& operator=(const PayOffBridge& original);
    private:
    PayOff* payOffPtr;
    };

inline double PayOffBridge::operator()(double Spot) const {
    return payOffPtr->operator ()(Spot);
}

#endif