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

// Constant

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

// Piecewise

ParameterPiecewiseConstant::ParameterPiecewiseConstant(std::vector<double>& constants_, std::vector<double>& points_) : constants(constants_), points(points_) {}

ParameterInner* ParameterPiecewiseConstant::clone() const {
    return new ParameterPiecewiseConstant(*this);
}

double ParameterPiecewiseConstant::integral(double time1, double time2) const {
    // Pathological cases:
    if(points[0] > time2)
        return (time2-time1)*constants[0];
    if(points.back() < time1)
        return (time2-time1)*constants.back();

    int i;
    double result = 0;
    bool first = true;
    for(i = 0; i < points.size(); i++){
        if(first && points[i] > time1){
            first = false;
            result += constants[i]*(points[i]-time1);
        } else { // i>0
            if(points[i] > time2)
               return result +  constants[i]*(time2-points[i-1]);
            result += constants[i]*(points[i]-points[i-1]);   
        }
    } // i = points.size()
    return result + constants[i]*(time2 - points[i-1]);
}

double ParameterPiecewiseConstant::integralSquare(double time1, double time2) const {
    // Pathological cases:
    if(points[0] > time2)
        return (time2-time1)*constants[0]*constants[0];
    if(points.back() < time1)
        return (time2-time1)*constants.back()*constants.back();

    int i;
    double result = 0;
    bool first = true;
    for(i = 0; i < points.size(); i++){
        if(first && points[i] > time1){
            first = false;
            result += constants[i]*constants[i]*(points[i]-time1);
        } else { // i>0
            if(points[i] > time2)
               return result +  constants[i]*constants[i]*(time2-points[i-1]);
            result += constants[i]*constants[i]*(points[i]-points[i-1]);   
        }
    } // i = points.size()
    return result + constants[i]*constants[i]*(time2 - points[i-1]);
}