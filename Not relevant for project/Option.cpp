#include "Option.hpp"

VanillaOption::VanillaOption(const PayOffBridge& payOff_, double expiry_) : expiry(expiry_), payOffBridge(payOff_) {}

double VanillaOption::getExpiry() const {
    return expiry;
}

double VanillaOption::payOff(double spot) const {
    return payOffBridge(spot);
}