#include<PayOffBridge.hpp>

PayOffBridge::PayOffBridge(const PayOffBridge& original) {
    payOffPtr = original.payOffPtr->clone();
}

PayOffBridge::PayOffBridge(const PayOff& innerPayOff) {
    payOffPtr = innerPayOff.clone();
}

PayOffBridge::~PayOffBridge() {
    delete payOffPtr;
}

PayOffBridge& PayOffBridge::operator= (const PayOffBridge& original){
    if (this != &original) {
        delete payOffPtr;
        payOffPtr = original.payOffPtr->clone();
    }
    return *this;
}