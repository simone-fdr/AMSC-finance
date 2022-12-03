#ifndef OPTION_HPP
#define OPTION_HPP

#include <PayOffBridge.h>

class VanillaOption{
    public:
    VanillaOption(const PayOffBridge& payOff_, double expiry_);
    double getExpiry() const;
    double payOff(double spot) const;
    private:
    double Expiry;
    PayOff* payOffPtr;
};
#endif