#include "PayOff.hpp"
#include <algorithm>
#include <math.h>

PayOffCall::PayOffCall(double strike_) : strike(strike_){}

double PayOffCall::operator () (double spot) const {
    return (spot-strike > 0) * (spot-strike);
}

PayOff* PayOffCall::clone() const {
    return new PayOffCall(*this);
}


PayOffPut::PayOffPut(double strike_) : strike(strike_) {}

double PayOffPut::operator () (double spot) const {
    return (strike-spot > 0) * (strike - spot);
}

PayOff* PayOffPut::clone() const {
    return new PayOffPut(*this);
}


PayOffDoubleDigital::PayOffDoubleDigital(double lowerLevel_, double upperLevel_)
                                        :lowerLevel(lowerLevel_), upperLevel(upperLevel_){}
// Checks if it is between low and up
double PayOffDoubleDigital::operator()(double spot) const {
    return (spot > lowerLevel && spot < upperLevel);
}

PayOff* PayOffDoubleDigital::clone() const {
    return new PayOffDoubleDigital(*this);
}


PayOffPowerCall::PayOffPowerCall(double strike_, double power_)
                                        :strike(strike_), power(power_){}

double PayOffPowerCall::operator()(double spot) const {
    return std::max(std::pow(spot, power) - strike, 0.);
}

PayOff* PayOffPowerCall::clone() const {
    return new PayOffPowerCall(*this);
}


PayOffPowerPut::PayOffPowerPut(double strike_, double power_)
                                        :strike(strike_), power(power_){}

double PayOffPowerPut::operator()(double spot) const {
    return std::max(strike - std::pow(spot, power), 0.);
}

PayOff* PayOffPowerPut::clone() const {
    return new PayOffPowerPut(*this);
}

PayOffBridge::PayOffBridge(const PayOffBridge& original) {
    payOffPtr = original.payOffPtr->clone();
}

PayOffBridge::PayOffBridge(const PayOff& innerPayOff) {
    payOffPtr = innerPayOff.clone();
}

PayOffBridge::~PayOffBridge() {
    delete payOffPtr;
}

PayOffBridge& PayOffBridge::operator= (const PayOffBridge& original){
    if (this != &original) {
        delete payOffPtr;
        payOffPtr = original.payOffPtr->clone();
    }
    return *this;
}

double PayOffForward::operator () (double spot) const {
    return spot-strike;
}

PayOffForward::PayOffForward(double strike_) : strike(strike_){}

PayOff* PayOffForward::clone() const {
    return new PayOffForward(*this);
}