#include <Option.hpp>

VanillaOption::VanillaOption(const BridgePayOff& payOff_, double expiry_) : expiry(expiry_) {}

double VanillaOption::getExpiry() const {
    return expiry;
}

double VanillaOption::payOff(double spot) const {
    return (*payOffPtr)(spot);
}