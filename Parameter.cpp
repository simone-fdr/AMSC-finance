#include "Parameter.hpp"

Parameter::Parameter(const ParameterInner& innerObject) {
    innerObjectPtr = innerObject.clone();
}

Parameter::Parameter(const Parameter& original) {
    innerObjectPtr = original.innerObjectPtr->clone();
}

Parameter& Parameter::operator=(const Parameter& original) {
    if (this != &original) {
        delete innerObjectPtr;
        innerObjectPtr = original.innerObjectPtr->clone();
    }
    return *this;
}

Parameter::~Parameter() {
    delete innerObjectPtr;
}

double Parameter::mean(double time1, double time2) const {
    double total = integral(time1,time2);
    return total/(time2-time1);
}

double Parameter::rootMeanSquare(double time1, double time2) const {
    double total = integralSquare(time1,time2);
    return total/(time2-time1);
}

ParameterConstant::ParameterConstant(double constant_) {
    constant = constant_;
    constantSquare = constant*constant;
}

ParameterInner* ParameterConstant::clone() const {
    return new ParameterConstant(*this);
}

double ParameterConstant::integral(double time1, double time2) const {
    return (time2-time1)*constant;
}

double ParameterConstant::integralSquare(double time1, double time2) const {
    return (time2-time1)*constantSquare;
}