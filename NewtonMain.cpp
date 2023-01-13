#include "NewtonMain.hpp"

int main() {
    double expiry = 5;
    double strike = 11;
    double spot = 9;
    double price = 9;
    double r = 0.05;
    double d = 0.01;
    double initialGuess = 1; //start guess
    double tolerance = 1e-4;

    std::unique_ptr<BS> bs;
    bs = std::make_unique<BSCall>(r,d,expiry,spot,strike);
    double vol = NewtonRaphson<BS, &BS::price, &BS::vega>(price, initialGuess, tolerance, *bs);
    double value = BlackScholesCall(spot,strike,r,d,vol,expiry);

    std::cout << "\n vol " << vol << " \nvalue of the option:" << value << "\n";
    return 0;
}