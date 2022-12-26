#ifndef TREE_HPP
#define TREE_HPP
#include "PayOff.hpp"

class Tree {
    public:
    Tree(double finalTime_);
    virtual double finalPayOff(double spot) const=0;
    virtual double preFinalValue(double spot, double time, double discountedFutureValue) const=0;
    virtual ~Tree(){}
    virtual Tree* clone() const=0;
    double getFinalTime() const;
    private:
    double finalTime;
};

class TreeAmerican : public Tree {
    public:
    TreeAmerican(double finalTime, const PayOffBridge& payOff_);
    virtual Tree* clone() const;
    virtual double finalPayOff(double spot) const;
    virtual double preFinalValue(double spot, double time, double discountedFutureValue) const;
    virtual ~TreeAmerican(){}
    private:
    PayOffBridge payOff;
};

class TreeEuropean : public Tree {
    public:
    TreeEuropean(double finalTime, const PayOffBridge& payOff_);
    virtual Tree* clone() const;
    virtual double finalPayOff(double spot) const;
    virtual double preFinalValue(double spot, double time, double discountedFutureValue) const;
    virtual ~TreeEuropean(){}
    private:
    PayOffBridge payOff;
};

#include <vector>
#include "Parameter.hpp"
#include "../Array.hpp"

class BinomialTree {
    public:
    BinomialTree(double spot_, const Parameter& r_, const Parameter& d_,
                 double volatility_, unsigned long steps, double time);
    double getThePrice(const Tree& product);
    protected:
    void buildTree();
    private:
    double spot;
    Parameter r;
    Parameter d;
    double volatility;
    unsigned long steps;
    double time;
    bool treeBuilt;
    std::vector<std::vector<std::pair<double, double>>> tree;
    FinArray discounts;
};

#endif