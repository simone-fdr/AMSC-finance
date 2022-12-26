#include "NewtonRaphson.hpp"
#include <cmath>
#include <iostream>
#include "BSCall.hpp"
#include "BlackScholes.hpp"
#include <memory>

using namespace std;
int main() {
    double expiry = 5;
    double strike = 11;
    double spot = 9;
    double price = 9;
    double r = 0.05;
    double d = 0.01;
    double start = 1; //start guess
    double tolerance = 1e-4;

    std::unique_ptr<BS> bs;
    bs = std::make_unique<BSCall>(r,d,expiry,spot,strike);
    double vol = NewtonRaphson<BS, &BS::price, &BS::vega>(price, start, tolerance, *bs);
    double value = BlackScholesCall(spot,strike,r,d,vol,expiry);
    cout << "\n vol " << vol << " \nvalue of the option:" << value << "\n";
    return 0;
}