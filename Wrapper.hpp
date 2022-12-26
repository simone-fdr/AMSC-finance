#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <memory>

template<class T>
class Wrapper {
    public:
    Wrapper(){
        dataPtr = 0;
    }

    Wrapper(const T& inner) {
        dataPtr = inner.clone();
    }

    Wrapper(T* dataPtr_ ) {
        dataPtr = dataPtr_;
    }

    ~Wrapper() {
        if (dataPtr != 0)
        delete dataPtr;
    }

    Wrapper(const Wrapper<T>& original) {
        if (original.dataPtr != 0)
            dataPtr = original.dataPtr->clone();
        else
            dataPtr=0;
    }

    Wrapper& operator=(const Wrapper<T>& original) {
        if (this != &original) {
            T* newPtr = (original.dataPtr !=0) ? original.dataPtr->clone() : 0;
            if (dataPtr!=0)
                delete dataPtr;
            dataPtr = newPtr;
        }
        return *this;
    }

    T& operator*() {
        return *dataPtr;
    }

    const T& operator*() const {
        return *dataPtr;
    }

    const T* const operator->() const {
        return dataPtr;
    }

    T* operator->() {
        return dataPtr;
    }

    private:
    T* dataPtr;
};

template<class T>
class CountedWrapper {
    public:
    CountedWrapper(){
        dataPtr = 0;
        *counter = 1;
    }

    CountedWrapper(const T& inner) {
        dataPtr = inner.clone();
        *counter = 1;
    }

    CountedWrapper(T* dataPtr_ ) {
        dataPtr = dataPtr_;
        *counter = 1;
    }

    // Destroys object only when counter reaches 0
    ~CountedWrapper() {
        if (decreaseCounter() != 0)
            if (dataPtr != 0)
                delete dataPtr;
    }

    CountedWrapper(const CountedWrapper<T>& original) {
        if (original.dataPtr != 0){
            dataPtr = original.dataPtr;
            increaseCounter();
        } else {
            dataPtr=0;
        }
    }

    CountedWrapper& operator=(const CountedWrapper<T>& original) {
        if (this != &original) {
            T* newPtr = (original.dataPtr != 0) ? original.dataPtr : 0;
            if (dataPtr!=0) {
                if(decreaseCounter() == 0){
                    delete dataPtr;
                }
            } else {
                *counter = 1;
            }
            dataPtr = newPtr;
        }
        return *this;
    }

    T& operator*() {
        return *dataPtr;
    }

    const T& operator*() const {
        return *dataPtr;
    }

    const T* const operator->() const {
        return dataPtr;
    }

    T* operator->() {
        return dataPtr;
    }

    int increaseCounter(){
        (*counter)++;
        return *counter;
    }

    int decreaseCounter(){
        (*counter)--;
        return *counter;
    }
    private:
    // I don't use shared_ptr for dataPtr otherwise it is all automatically implemented, making the exercise trivial
    T* dataPtr;
    std::shared_ptr<int> counter;
};

#endif