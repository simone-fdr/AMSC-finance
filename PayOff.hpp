#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <map>
#include <string>

class PayOff{
    public:
    PayOff(){};
    virtual PayOff* clone() const=0;
    virtual double operator()(double spot) const = 0;
    virtual ~PayOff(){};
    private:
};

class PayOffCall : public PayOff {
    public:
    PayOffCall(double strike_);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffCall(){}
    private:
    double strike;
};

class PayOffPut : public PayOff {
    public:
    PayOffPut(double strike_);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffPut(){}
    private:
    double strike;
};

class PayOffDoubleDigital : public PayOff {
    public:
    // Generic constructor (In order to be able to use the Factory)
    PayOffDoubleDigital(double strike_);
    // Specific constructor
    PayOffDoubleDigital(double lowerLevel_, double upperLevel_);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffDoubleDigital(){}
    private:
    double lowerLevel;
    double upperLevel;
};

class PayOffPowerCall : public PayOff{
    public:
    PayOffPowerCall(double strike_, double power);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffPowerCall(){}
    private:
    double strike;
    double power;
};

class PayOffPowerPut : public PayOff{
    public:
    PayOffPowerPut(double strike_, double power);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffPowerPut(){}
    private:
    double strike;
    double power;
};

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

class PayOffForward : public PayOff {
    public:
    PayOffForward(double strike_);
    virtual double operator()(double spot) const;
    virtual ~PayOffForward(){}
    virtual PayOff* clone() const;
    private:
    double strike;
};

class PayOffFactory {
    public:
    typedef PayOff* (*CreatePayOffFunction)(double);
    static PayOffFactory& instance();
    void registerPayOff(std::string, CreatePayOffFunction);
    PayOff* createPayOff(std::string payOffId, double strike);
    ~PayOffFactory(){};
    private:
    std::map<std::string, CreatePayOffFunction> creatorFunctions;
    PayOffFactory(){}
    PayOffFactory(const PayOffFactory&){}
    PayOffFactory& operator= (const PayOffFactory&){ return *this;}
};

// HELPER

template <class T>
class PayOffHelper {
    public:
    PayOffHelper(std::string);
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