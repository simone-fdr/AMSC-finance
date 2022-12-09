#ifndef WRAPPER_HPP
#define WRAPPER_HPP

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

#endif