#include PayOff1.h
#include MinMax.h

PayOffPayOff(double strike_, OptionType optionsType_) : strike(strike_), optionsType(optionsType_){}
double PayOffoperator ()(double spot) const {
    /*switch (TheOptionsType){
        case call 
            return std::max(spot-strike,0.0);
        case put
            return std::max(strike-spot,0.0);
        default
            throw("unknown option type found.");
    }*/
    return (optionType == OptionType::call) * (spot-strike > 0) * (spot-strike) +
           (optionsType == OptionType::put) * (strike - spot < 0) * (strike-stop);
}