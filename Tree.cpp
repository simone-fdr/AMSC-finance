#include "Tree.hpp"
#include "Array.hpp"
#include <cmath>
#include <minmax.h>

Tree::Tree(double finalTime_) : finalTime(finalTime_) {}

double Tree::getFinalTime() const {
    return finalTime;
}

TreeAmerican::TreeAmerican(double finalTime, const PayOffBridge& payOff_) : Tree(finalTime), payOff(payOff_) {}

Tree* TreeAmerican::clone() const {
    return new TreeAmerican(*this);
}

double TreeAmerican::finalPayOff(double spot) const {
    return payOff(spot);
}

double TreeAmerican::preFinalValue(double spot, double time, double discountedFutureValue) const {
    return std::max(payOff(spot), discountedFutureValue);
}

TreeEuropean::TreeEuropean(double finalTime, const PayOffBridge& payOff_): Tree(finalTime), payOff(payOff_) {}

double TreeEuropean::finalPayOff(double spot) const {
    return payOff(spot);
}

double TreeEuropean::preFinalValue(double spot, double time, double discountedFutureValue) const {
    return discountedFutureValue;
}

Tree* TreeEuropean::clone() const {
    return new TreeEuropean(*this);
}

BinomialTree::BinomialTree(double spot_, const Parameter& r_, const Parameter& d_,
                           double volatility_, unsigned long steps_, double time_):
    spot(spot_), r(r_), d(d_), volatility(volatility_), steps(steps_), time(time_), discounts(steps) { 
    treeBuilt=false;
}

void BinomialTree::buildTree() {
    treeBuilt = true;
    tree.resize(steps+1);
    double initialLogSpot = std::log(spot);
    for (unsigned long i=0; i <=steps; i++) {
        tree[i].resize(i+1);
        double thisTime = (i*time)/steps;
        double movedLogSpot = initialLogSpot + r.integral(0.0, thisTime) - d.integral(0.0, thisTime);
        movedLogSpot -= 0.5*volatility*volatility*thisTime;
        double sd = volatility*std::sqrt(time/steps);
        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+2,k++)
            tree[i][k].first = std::exp(movedLogSpot+ j*sd);
    }
    for (unsigned long l=0; l < steps; l++) {
        discounts[l] = std::exp(- r.integral(l*time/steps,(l+1)*time/steps));
    }
}

double BinomialTree::getThePrice(const Tree& product) {
    if (!treeBuilt)
        buildTree();
    if (product.getFinalTime() != time)
        throw("mismatched product in SimpleBinomialTree");
    for (long j = -static_cast<long>(steps), k=0; j <=static_cast<long>(steps); j=j+2,k++)
        tree[steps][k].second = product.finalPayOff(tree[steps][k].first);
    for (unsigned long i=1; i <= steps; i++) {
        unsigned long index = steps-i;
        double thisTime = index*time/steps;
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+2,k++) {
            double spot = tree[index][k].first;
            double futureDiscountedValue = 0.5*discounts[index]* (tree[index+1][k].second + tree[index+1][k+1].second);
            tree[index][k].second = product.preFinalValue(spot, thisTime, futureDiscountedValue);
        }
    }
    return tree[0][0].second;
}