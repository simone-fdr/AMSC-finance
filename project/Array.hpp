#ifndef FINARRAY_HPP
#define FINARRAY_HPP

#include<algorithm>
#include<numeric>

// class that redeclares the functionality of a vector with extra utilities
class FinArray {
    public:
    explicit FinArray(unsigned long actualSize=0);
    FinArray(const FinArray& original);
    ~FinArray();
    // Element wise operations
    FinArray& operator=(const FinArray& original);
    FinArray& operator=(const double& val);
    FinArray& operator+=(const FinArray& operand);
    FinArray& operator-=(const FinArray& operand);
    FinArray& operator/=(const FinArray& operand);
    FinArray& operator*=(const FinArray& operand);
    // Scalar operations
    FinArray& operator+=(const double& operand);
    FinArray& operator-=(const double& operand);
    FinArray& operator/=(const double& operand);
    FinArray& operator*=(const double& operand);
    // Map function
    FinArray apply(double f(double)) const;
    // Access operator
    inline double operator[](unsigned long i) const;
    inline double& operator[](unsigned long i);
    // Utilities
    inline unsigned long size() const;
    void resize(unsigned long newSize);
    double sum() const;
    double min() const;
    double max() const;
    private:
    double* valuesPtr;
    double* endPtr;
    unsigned long actualSize;
    unsigned long capacity;
};

inline double FinArray::operator[](unsigned long i) const {
    #ifdef RANGE_CHECKING
    if (i >= actualSize) {
        throw("Index out of bounds");
    }
    #endif
    return valuesPtr[i];
}

inline double& FinArray::operator[](unsigned long i) {
    #ifdef RANGE_CHECKING
    if (i >= actualSize) {
        throw("Index out of bounds");
    }
    #endif
    return valuesPtr[i];
}

inline unsigned long FinArray::size() const {
    return actualSize;
}

#endif // ifndef FINARRAY_HPP