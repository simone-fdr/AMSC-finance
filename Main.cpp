#include "SimpleMC.hpp"
#include <iostream>
#include "Option.hpp"
#include "Statistic.hpp"
#include "ConvergenceTable.hpp"
#include "ParkMiller.hpp"
#include "AntiThetic.hpp"

int main(){
    double expiry;
    double strike;
    double spot;
    double vol;
    double r;
    unsigned long numberOfPaths;


    std::cout << "\nEnter expiry\n";
    std::cin >> expiry;

    std::cout << "\nEnter strike\n";
    std::cin >> strike;
    
    std::cout << "\nEnter spot\n";
    std::cin >> spot;
    
    std::cout << "\nEnter vol\n";
    std::cin >> vol;
    
    std::cout << "\nr\n";
    std::cin >> r;
    
    std::cout << "\nNumber of paths\n";
    std::cin >> numberOfPaths;

    PayOffCall payOff(strike);
    
    VanillaOption option(payOff, expiry);
    
    ParameterConstant volParam(vol);
    ParameterConstant rParam(r);
    
    StatisticMean gatherer;
    ConvergenceTable gathererTwo(gatherer);

    RandomParkMiller generator(1);
    AntiThetic genTwo(generator);

    simpleMonteCarlo(option, spot, volParam, rParam, numberOfPaths, gathererTwo, genTwo);

    std::vector<std::vector<double>> results = gathererTwo.getResultsSoFar();
    
    std::cout <<"\nFor the call price the results are \n";
    for (unsigned long i=0; i < results.size(); i++) {
        for (unsigned long j=0; j < results[i].size(); j++)
            std::cout << results[i][j] << " ";
        std::cout << std::endl;
    }

    return 0;
}