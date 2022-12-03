#include "Array.hpp"
#include<algorithm>
#include<numeric>

FinArray::FinArray(unsigned long actualSize_) : actualSize(actualSize_), capacity(actualSize_) {
    if (actualSize > 0) {
        valuesPtr = new double[actualSize];
        endPtr = valuesPtr;
        endPtr += actualSize;
    } else {
        valuesPtr=0;
        endPtr=0;
    }
}

FinArray::FinArray(const FinArray& original) : actualSize(original.actualSize), capacity(original.actualSize) {
    if (actualSize > 0) {
        valuesPtr = new double[actualSize];
        endPtr = valuesPtr;
        endPtr += actualSize;
        std::copy(original.valuesPtr, original.endPtr, valuesPtr);
    } else {
        valuesPtr = endPtr =0;
    }
}

FinArray::~FinArray() {
    if (valuesPtr >0)
    delete [] valuesPtr;
}

FinArray& FinArray::operator=(const FinArray& original) {
    if (&original == this)
        return *this;
    if (original.actualSize > capacity) {
        if (capacity > 0)
            delete [] valuesPtr;
        valuesPtr = new double[original.actualSize];
        capacity = original.actualSize;
    }
    actualSize=original.actualSize;
    endPtr = valuesPtr;
    endPtr += actualSize;
    std::copy(original.valuesPtr, original.endPtr, valuesPtr);
    return *this;
}

void FinArray::resize(unsigned long newSize) {
    if (newSize > capacity) {
        if (capacity > 0)
            delete [] valuesPtr;
        valuesPtr = new double[newSize];
        capacity = newSize;
    }
    actualSize = newSize;
    endPtr = valuesPtr + actualSize;
}

FinArray& FinArray::operator+=(const FinArray& operand) {
    #ifdef RANGE_CHECKING
    if ( actualSize != operand.actualSize()) {
      throw("to apply += two arrays must be of same size");
    }
    #endif
    for (unsigned long i =0; i < actualSize; i++)
        valuesPtr[i]+=operand[i];
    return *this;
}

FinArray& FinArray::operator-=(const FinArray& operand) {
    #ifdef RANGE_CHECKING
    if (actualSize != operand.actualSize()) {
        throw("to apply -= two arrays must be of same size");
    }
    #endif
    for (unsigned long i =0; i < actualSize; i++)
        valuesPtr[i]-=operand[i];
    return *this;
}

FinArray& FinArray::operator/=(const FinArray& operand) {
    #ifdef RANGE_CHECKING
    if ( actualSize != operand.actualSize()) {
        throw("to apply /= two arrays must be of same size");
    }
    #endif
    for (unsigned long i =0; i < actualSize; i++)
        valuesPtr[i]/=operand[i];
    return *this;
}
FinArray& FinArray::operator*=(const FinArray& operand) {
    #ifdef RANGE_CHECKING
    if ( actualSize != operand.actualSize()) {
        throw("to apply *= two arrays must be of same size");
    }
    #endif
    for (unsigned long i =0; i < actualSize; i++)
    valuesPtr[i]*=operand[i];
    return *this;
}

/////////////////////////////

FinArray& FinArray::operator+=(const double& operand) {
    for (unsigned long i =0; i < actualSize; i++)
    valuesPtr[i]+=operand;
    return *this;
}

FinArray& FinArray::operator-=(const double& operand) {
    for (unsigned long i =0; i < actualSize; i++)
    valuesPtr[i]-=operand;
    return *this;
}

FinArray& FinArray::operator/=(const double& operand) {
    for (unsigned long i =0; i < actualSize; i++)
    valuesPtr[i]/=operand;
    return *this;
}

FinArray& FinArray::operator*=(const double& operand) {
    for (unsigned long i =0; i < actualSize; i++)
    valuesPtr[i]*=operand;
    return *this;
}

FinArray& FinArray::operator=(const double& val) {
    for (unsigned long i =0; i < actualSize; i++)
    valuesPtr[i]=val;
    return *this;
}

double FinArray::sum() const {
    return std::accumulate(valuesPtr,endPtr,0.0);
}

double FinArray::min() const {
    #ifdef RANGE_CHECKING
    if ( actualSize==0) {
      throw("cannot take min of empty array");
    }
    #endif
    double* tmp = valuesPtr;
    double* endTmp = endPtr;
    return *std::min_element(tmp,endTmp);
}

double FinArray::max() const {
    #ifdef RANGE_CHECKING
    if ( actualSize==0) {
        throw("cannot take max of empty array");
    }
    #endif
    double* tmp = valuesPtr;
    double* endTmp = endPtr;
    return *std::max_element(tmp,endTmp);
}

FinArray FinArray::apply(double f(double)) const {
    FinArray result(size());
    std::transform(valuesPtr,endPtr,result.valuesPtr,f);
    return result;
}