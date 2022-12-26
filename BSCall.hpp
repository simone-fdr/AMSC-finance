#ifndef BS_CALL_HPP
#define BS_CALL_HPP

class BS {
    public:
    BSCall(double r_, double d_, double t_, double spot_, double strike_);
    virtual double price(double Vol) const = 0;
    virtual double vega(double Vol) const = 0;
    private:
    double r;
    double d;
    double t;
    double spot;
    double strike;
};

class BSCall : public BS{
    public:
    BSCall(double r_, double d_, double t_, double spot_, double strike_);
    virtual double price(double Vol) const;
    virtual double vega(double Vol) const;
    private:
    double r;
    double d;
    double t;
    double spot;
    double strike;
};

class BSPut : public BS{
    public:
    BSPut(double r_, double d_, double t_, double spot_, double strike_);
    virtual double price(double Vol) const;
    virtual double vega(double Vol) const;
    private:
    double r;
    double d;
    double t;
    double spot;
    double strike;
};

#endif