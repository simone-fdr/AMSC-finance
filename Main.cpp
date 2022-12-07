#include "BlackScholes.hpp"
#include <cmath>
#include <iostream>
#include "Solver.hpp"
#include "BSCall.hpp"

int main(){
    double expiry;
    double strike;
    double spot;
    double r;
    double d;
    double price;

    std::cout << "\nEnter expiry\n";
    std::cin >> expiry;

    std::cout << "\nEnter strike\n";
    std::cin >> strike;
    
    std::cout << "\nEnter spot\n";
    std::cin >> spot;
    
    std::cout << "\nEnter price\n";
    std::cin >> price;
    
    std::cout << "\nr\n";
    std::cin >> r;

    std::cout << "\nd\n";
    std::cin >> d;
    
    double start;

    std::cout << "\nInitial guess\n";
    std::cin >> start;

    double tolerance;

    std::cout << "\nTolerance\n";
    std::cin >> tolerance;

    BSCall call(r,d,expiry,spot, strike);

    double vol = NewtonRaphson<BSCall, &BSCall::price, &BSCall::vega>(price, start, tolerance, call);
    
    double priceTwo = BlackScholesCall(spot,strike,r,d,vol,expiry);
    
    std::cout << "\n vol " << vol << " \nprice two:" << priceTwo << std::endl;

    return 0;
}