#ifndef BS_CALL_HPP
#define BS_CALL_HPP
#include "BlackScholes.hpp"

// Abstract class representing an option in Black-Scholes, used in Newton method to approximate
class BS {
    public:
    BS() = default;
    //! @returns the price
    //! @param vol volatility
    virtual double price(double Vol) const = 0;

    //! @returns the derivative of price
    //! @param vol volatility
    virtual double vega(double Vol) const = 0;

    private:
    // risk-free market return
    double r;
    // dividend yields
    double d;
    // expiry date
    double t;
    // spot of option
    double spot;
    // strike of option
    double strike;
};

class BSCall : public BS{
    public:
    // Constructor that sets the variables
    BSCall(double r_, double d_, double t_, double spot_, double strike_);
    //! @returns the price
    //! @param vol volatility
    virtual double price(double Vol) const;

    //! @returns the derivative of price
    //! @param vol volatility
    virtual double vega(double Vol) const;
    private:
    // risk-free market return
    double r;
    // dividend yields
    double d;
    // expiry date
    double t;
    // spot of option
    double spot;
    // strike of option
    double strike;
};

class BSPut : public BS{
    public:
    // Constructor that sets the variables
    BSPut(double r_, double d_, double t_, double spot_, double strike_);
    //! @returns the price
    //! @param vol volatility
    virtual double price(double Vol) const;

    //! @returns the derivative of price
    //! @param vol volatility
    virtual double vega(double Vol) const;
    private:
    // risk-free market return
    double r;
    // dividend yields
    double d;
    // expiry date
    double t;
    // spot of option
    double spot;
    // strike of option
    double strike;
};

#endif