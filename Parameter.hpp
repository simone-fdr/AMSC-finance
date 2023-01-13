#ifndef Parameter_HPP
#define Parameter_HPP

#include <vector>

// Abstract class that represent a parameter
class ParameterInner {
    public:
    ParameterInner() = default;
    // Clone constructor
    virtual ParameterInner* clone() const=0;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the funtion 
    //      between the two boundary
    virtual double integral(double time1, double time2) const=0;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the function
    //      squared between the two boundary
    virtual double integralSquare(double time1, double time2) const=0;
    virtual ~ParameterInner() = default;
    private:
};

// 
class Parameter {
    public:
    // Constructor with an ParameterInner
    Parameter(const ParameterInner& innerObject);
    // Copy constructor
    Parameter(const Parameter& original);
    // Assignment constructor
    Parameter& operator=(const Parameter& original);
    virtual ~Parameter();
    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the funtion 
    //      in the innerObject between the two boundary
    inline double integral(double time1, double time2) const;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the function
    //      in the innerObject squared between the two boundary
    inline double integralSquare(double time1, double time2) const;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the mean of the function in the innerObject
    //      between the two boundary
    double mean(double time1, double time2) const;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the root mean square of the function 
    //      in the innerObject between the two boundary
    double rootMeanSquare(double time1, double time2) const;
    private:
    // InnerParameter that stores the function
    ParameterInner* innerObjectPtr;
};

// Inline function defined in the header
inline double Parameter::integral(double time1, double time2) const {
    return innerObjectPtr->integral(time1,time2);
}

// Inline function defined in the header
inline double Parameter::integralSquare(double time1, double time2) const {
    return innerObjectPtr->integralSquare(time1,time2);
}


class ParameterConstant : public ParameterInner {
    public:
    // Constructor of a constant function
    //! @param constant_ which the function takes
    ParameterConstant(double constant_);

    // Clone constructor
    virtual ParameterInner* clone() const;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the funtion 
    //      in the innerObject between the two boundary
    virtual double integral(double time1, double time2) const;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the function
    //      in the innerObject squared between the two boundary
    virtual double integralSquare(double time1, double time2) const;
    private:
    // Value of the function
    double constant;
    // Value of the function squared
    double constantSquare;
};

class ParameterPiecewiseConstant : public ParameterInner {
    public:
    //! @pre points.size() == constants.size() - 1
    //! @param points_ where the values changes
    //! @param constants_ which the functin takes after change
    ParameterPiecewiseConstant(std::vector<double>& constants_, std::vector<double>& points_);
    virtual ParameterInner* clone() const;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the funtion 
    //      in the innerObject between the two boundary
    virtual double integral(double time1, double time2) const;

    //! @pre time1 <= time2
    //! @param time1 start of domain
    //! @param time2 end of domain
    //! @returns the definite integral of the function
    //      in the innerObject squared between the two boundary
    virtual double integralSquare(double time1, double time2) const;
    private:
    // Values of functions
    std::vector<double> constants;
    // Points of change of definition of the function
    std::vector<double> points;
};

#endif