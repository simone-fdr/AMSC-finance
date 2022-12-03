#ifndef PAYOFF_HPP
#define PAYOFF_HPP

class AbstractPayOff{
    public:
    PayOff(){};
    virtual PayOff* clone() const=0;
    virtual double operator()(double spot) const = 0;
    virtual ~PayOff(){};
    private:
};

class PayOffCall : public AbstractPayOff {
    public:
    PayOffCall(double strike_);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffCall(){}
    private:
    double strike;
};

class PayOffPut : public AbstractPayOff {
    public:
    PayOffPut(double strike_);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffPut(){}
    private:
    double strike;
};

class PayOffDoubleDigital : public AbstractPayOff {
    public:
    PayOffDoubleDigital(double lowerLevel_, double upperLevel_);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffDoubleDigital(){}
    private:
    double lowerLevel;
    double upperLevel;
};

class PayOffPowerCall : public AbstractPayOff{
    public:
    PayOffPowerCall(double strike_, double power);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffPowerCall(){}
    private:
    double strike;
    double power;
}

class PayOffPowerPut : public AbstractPayOff{
    public:
    PayOffPowerPut(double strike_, double power);
    virtual PayOff* clone() const;
    virtual double operator()(double spot) const;
    virtual ~PayOffPowerPut(){}
    private:
    double strike;
    double power;
}

#endif