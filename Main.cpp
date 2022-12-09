#include "BlackScholes.hpp"
#include <cmath>
#include <iostream>
#include "Solver.hpp"
#include "PayOff.hpp"
#include "BSCall.hpp"
#include "Statistic.hpp"
#include "Parameter.hpp"
#include "Antithetic.hpp"
#include "ParkMiller.hpp"
#include "Statistic.hpp"
#include "ConvergenceTable.hpp"
#include "Option.hpp"
#include "SimpleMC.hpp"
#include <chrono>

int main(){
    /*double expiry;
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

    /*
    Exercise 2
    */

    double strike = 10;
    double expiry = 100;
    double spot = 9;
    double vol = 3;
    double r = 2;
    unsigned long numberOfPaths = 8;
    
    ParameterConstant volParam(vol);
    ParameterConstant rParam(r);

    StatisticMean gatherer;
    ConvergenceTable gathererTwo(gatherer);

    RandomParkMiller generator(1);
    AntiThetic genTwo(generator);

    PayOff* payOffPtr = PayOffFactory::instance().createPayOff("call", strike);
    VanillaOption option(*payOffPtr, expiry);


    auto start = std::chrono::steady_clock::now();
    simpleMonteCarlo(option, spot, volParam, rParam, numberOfPaths, gathererTwo, genTwo);
    auto end = std::chrono::steady_clock::now();
    double elapsed_time = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count());

    std::vector<std::vector<double>> results = gathererTwo.getResultsSoFar();
    std::cout <<"For the call price the results are" << std::endl;
    for (unsigned long i=0; i < results.size(); i++) {
        for (unsigned long j=0; j < results[i].size(); j++)
            std::cout << results[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << "It took " << elapsed_time << " nanoseconds" << std::endl;

    return 0;
}