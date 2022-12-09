#ifndef Parameter_HPP
#define Parameter_HPP

#include <vector>
class ParameterInner {
    public:
    ParameterInner(){}
    virtual ParameterInner* clone() const=0;
    virtual double integral(double time1, double time2) const=0;
    virtual double integralSquare(double time1, double time2) const=0;
    virtual ~ParameterInner(){}
    private:
};

class Parameter {
    public:
    Parameter(const ParameterInner& innerObject);
    Parameter(const Parameter& original);
    Parameter& operator=(const Parameter& original);
    virtual ~Parameter();
    inline double integral(double time1, double time2) const;
    inline double integralSquare(double time1, double time2) const;
    double mean(double time1, double time2) const;
    double rootMeanSquare(double time1, double time2) const;
    private:
    ParameterInner* innerObjectPtr;
};

inline double Parameter::integral(double time1, double time2) const {
    return innerObjectPtr->integral(time1,time2);
}

inline double Parameter::integralSquare(double time1, double time2) const {
    return innerObjectPtr->integralSquare(time1,time2);
}

class ParameterConstant : public ParameterInner {
    public:
    ParameterConstant(double constant_);
    virtual ParameterInner* clone() const;
    virtual double integral(double time1, double time2) const;
    virtual double integralSquare(double time1, double time2) const;
    private:
    double constant;
    double constantSquare;
};

class ParameterPiecewiseConstant : public ParameterInner {
    public:
    // Points where the values changes, points.size() == constants.size() - 1
    ParameterPiecewiseConstant(std::vector<double>& constants_, std::vector<double>& points_);
    virtual ParameterInner* clone() const;
    virtual double integral(double time1, double time2) const;
    virtual double integralSquare(double time1, double time2) const;
    private:
    std::vector<double> constants;
    std::vector<double> points;
};

#endif