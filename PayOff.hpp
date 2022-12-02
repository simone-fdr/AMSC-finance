#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff{
    public:
    enum OptionType {call, put};
    PayOff(double strike_, OptionType optionsType_);
    double operator()(double spot) const;
    private:
    double strike;
    OptionType optionsType;
};
#endif