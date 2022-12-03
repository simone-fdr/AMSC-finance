#ifndef FINARRAY_HPP
#define FINARRAY_HPP

class FinArray {
    public:
    explicit FinArray(unsigned long actualSize=0);
    FinArray(const FinArray& original);
    ~FinArray();
    FinArray& operator=(const FinArray& original);
    FinArray& operator=(const double& val);
    FinArray& operator+=(const FinArray& operand);
    FinArray& operator-=(const FinArray& operand);
    FinArray& operator/=(const FinArray& operand);
    FinArray& operator*=(const FinArray& operand);
    FinArray& operator+=(const double& operand);
    FinArray& operator-=(const double& operand);
    FinArray& operator/=(const double& operand);
    FinArray& operator*=(const double& operand);
    FinArray apply(double f(double)) const;
    inline double operator[](unsigned long i) const;
    inline double& operator[](unsigned long i);
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