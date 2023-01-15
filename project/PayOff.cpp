#include "PayOff.hpp"

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


PayOffDoubleDigital::PayOffDoubleDigital(double lowerLevel_, double upperLevel_) :lowerLevel(lowerLevel_), upperLevel(upperLevel_){}

PayOffDoubleDigital::PayOffDoubleDigital(double strike_) :lowerLevel(strike_*1.1), upperLevel(strike_*0.9){}


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

//FACTORY

void PayOffFactory::registerPayOff(std::string payOffId, CreatePayOffFunction creatorFunction) {
    creatorFunctions.insert(std::pair<std::string,CreatePayOffFunction>(payOffId,creatorFunction));
}

PayOff* PayOffFactory::createPayOff(std::string payOffId, double strike) {
    std::map<std::string, CreatePayOffFunction>::const_iterator i = creatorFunctions.find(payOffId);
    if (i == creatorFunctions.end()) {
        std::cout << payOffId << " is an unknown payoff" << std::endl;
        return NULL;
    }
    return (i->second)(strike);
}

PayOffFactory& PayOffFactory::instance() {
    static PayOffFactory factory;
    return factory;
}

// Helper

namespace 
{
    PayOffHelper<PayOffCall> registerCall("call");
    PayOffHelper<PayOffPut> registerPut("put");
    PayOffHelper<PayOffForward> registerForward("forward");
    PayOffHelper<PayOffDoubleDigital> registerDoubleDigital("doubledigital");
}