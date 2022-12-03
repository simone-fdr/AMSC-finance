#include <Random.hpp>
#include <SimpleMC.hpp>
#include <iostream>
#include <cmath>

double simpleMonteCarlo(const VanillaOption& option, double spot,
                        Parameter& vol, Parameter& r, unsigned long numberOfPaths){
    double expiry = option.getExpiry();
    double variance = vol.integralSquare(0, expiry);
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5*variance;
    double movedSpot = spot*std::exp(r.integral(0, expiry) + itoCorrection);
    double thisSpot;
    double sum=0;
    for (unsigned long i=0; i < NumberOfPaths; i++){
        double gaussian = getOneGaussianByBoxMuller();
        thisSpot = movedSpot*std::exp(rootVariance*gaussian);
        double payOff = option.payOff(thisSpot);
        sum += payOff;
    }
    double mean = sum / numberOfPaths;
    mean *= exp(-r.integral(0,expiry));
    return mean;
}

// TODO implement switch that decides which type of payoff
int main(){
    double expiry;
    double low,up;
    double strike;
    double spot;
    double vol;
    double r;
    unsigned long numberOfPaths;


    std::cout << "\nEnter expiry\n";
    std::cin >> expiry;

    std::cout << "\nEnter low barrier\n";
    std::cin >> low;
    
    std::cout << "\nEnter up barrier\n";
    std::cin >> up

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
    /*
    Wrong since it exits the scope
    if (optionType== 0)
        PayOffCall payOff(Strike);
    else
        PayOffPut payOff(Strike);
    */

    ParametersConstant volParam(Vol);
    ParametersConstant rParam(r);
    PayOffCall payOff(strike);
    VanillaOption option(payOff, expiry);


    double result = simpleMonteCarlo(option, spot,
                                        volParam, rParam, numberOfPaths);


    std::cout <<"the price is " << result << std::endl;
    return 0;
}