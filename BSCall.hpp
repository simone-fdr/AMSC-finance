#ifndef BS_CALL_HPP
#define BS_CALL_HPP

class BSCall {
    public:
    BSCall(double r_, double d_, double t_, double spot_, double strike_);
    double price(double Vol) const;
    double vega(double Vol) const;
    private:
    double r;
    double d;
    double t;
    double spot;
    double strike;
};
#endif