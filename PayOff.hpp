#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <map>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>

// Abstract class representing a PayOff
// The overload of the operator make the instance callable
class PayOff{
    public:
    // Constructor
    PayOff() = default;
    // Clone constructor
    virtual PayOff* clone() const=0;
    //! @param spot of the option
    //! @returns the payoff
    virtual double operator()(double spot) const = 0;
    // Deconstructor
    virtual ~PayOff() = default;
    private:
};

class PayOffCall : public PayOff {
    public:
    // Constructor
    //! @param strike of the option
    PayOffCall(double strike_);
    // Clone constructor
    virtual PayOff* clone() const;
    //! @param spot of the option
    //! @returns the payoff of the call
    virtual double operator()(double spot) const;
    // Deconstructor
    virtual ~PayOffCall() = default;
    private:
    // Strike of the option
    double strike;
};

class PayOffPut : public PayOff {
    public:
    // Constructor
    //! @param strike of the option
    PayOffPut(double strike_);
    // Clone constructor
    virtual PayOff* clone() const;
    //! @param spot of the option
    //! @returns the payoff of the put
    virtual double operator()(double spot) const;
    // Deconstructor
    virtual ~PayOffPut() = default;
    private:
    // Strike of the option
    double strike;
};

class PayOffDoubleDigital : public PayOff {
    public:
    // Generic constructor (In order to be able to use the Factory)
    PayOffDoubleDigital(double strike_);
    // Specific constructor
    //! @param lowerLevel_ lower bound of the value
    //! @param upperLevel_ upper bound of the value
    PayOffDoubleDigital(double lowerLevel_, double upperLevel_);
    // Clone constructor
    virtual PayOff* clone() const;
    //! @param spot of the option
    //! @returns the payoff of the double digital
    virtual double operator()(double spot) const;
    // Deconstructor
    virtual ~PayOffDoubleDigital() = default;
    private:
    // lower bound
    double lowerLevel;
    // upper bound
    double upperLevel;
};

class PayOffPowerCall : public PayOff{
    public:
    // Constructor
    //! @param strike of the option
    //! @param power used in calculation
    PayOffPowerCall(double strike_, double power);
    // Clone constructor
    virtual PayOff* clone() const;
    //! @param spot of the option
    //! @returns the payoff of the power call
    virtual double operator()(double spot) const;
    // Deconstructor
    virtual ~PayOffPowerCall() = default;
    private:
    // Strike of the option
    double strike;
    // Power used in calculation
    double power;
};

class PayOffPowerPut : public PayOff{
    public:
    // Constructor
    //! @param strike of the option
    PayOffPowerPut(double strike_, double power);
    // Clone constructor
    virtual PayOff* clone() const;
    //! @param spot of the option
    //! @returns the payoff of the power put
    virtual double operator()(double spot) const;
    // Deconstructor
    virtual ~PayOffPowerPut() = default;
    private:
    // Strike of the option
    double strike;
    // Power used in calculation
    double power;
};

class PayOffBridge {
    public:
    // Copy constructor
    PayOffBridge(const PayOffBridge& original);
    // Constructor that helps with memory management
    PayOffBridge(const PayOff& innerPayOff);
    //! @param spot of the option
    //! @returns the payoff
    inline double operator()(double spot) const;
    // Deconstructor
    ~PayOffBridge();
    // Assignment constructor
    PayOffBridge& operator=(const PayOffBridge& original);
    private:
    // Pointer to the real Payoff calculator
    PayOff* payOffPtr;
};

// Inline functions go in header
inline double PayOffBridge::operator()(double spot) const {
    return payOffPtr->operator()(spot);
}

class PayOffForward : public PayOff {
    public:
    // Constructor
    //! @param strike of the option
    PayOffForward(double strike_);
    //! @param spot of the option
    //! @returns the payoff forward
    virtual double operator()(double spot) const;
    // Deconstructor
    virtual ~PayOffForward() = default;
    // Clone constructor
    virtual PayOff* clone() const;
    private:
    // Strike of the option
    double strike;
};

class PayOffFactory {
    public:
    typedef PayOff* (*CreatePayOffFunction)(double);
    // create a instance of PayOff
    static PayOffFactory& instance();
    // Registers a string as a class
    void registerPayOff(std::string, CreatePayOffFunction);
    // Creates a PayOff using
    //! @param payOffId string id
    //! @param strike of the option
    PayOff* createPayOff(std::string payOffId, double strike);
    // Deconstructor
    ~PayOffFactory() = default;
    private:
    // map of ids
    std::map<std::string, CreatePayOffFunction> creatorFunctions;
    // default constructor, not public
    PayOffFactory() = default;
    // Private copy constructor
    PayOffFactory(const PayOffFactory&){}
    // Private assignment constructor
    PayOffFactory& operator= (const PayOffFactory&){ return *this;}
};

// HELPER

// Helper class used by the factor to assign strings to payoff classes
template <class T>
class PayOffHelper {
    public:
    // Assigns a string to class
    PayOffHelper(std::string);
    // Creates a class of type PayOff
    //! @param strike of option
    static PayOff* create(double);
};

template <class T>
PayOff* PayOffHelper<T>::create(double strike) {
    return new T(strike);
}

template <class T>
PayOffHelper<T>::PayOffHelper(std::string id) {
    PayOffFactory& payOffFactory = PayOffFactory::instance();
    payOffFactory.registerPayOff(id, PayOffHelper<T>::create);
}

#endif