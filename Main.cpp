#include "AntiThetic.hpp"
#include "BlackScholes.hpp"
#include "ConvergenceTable.hpp"
#include "ExoticEngine.hpp"
#include "Option.hpp"
#include "ParkMiller.hpp"
#include "Path.hpp"
#include "SimpleMC.hpp"
#include "Statistic.hpp"
#include "Tree.hpp"
#include <cmath>
#include <iostream>

int main(){
    double expiry;
    double strike;
    double spot;
    double vol;
    double r;
    double d;
    unsigned long steps;

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

    std::cout << "\nd\n";
    std::cin >> d;
    
    std::cout << "\nNumber of steps\n";
    std::cin >> steps;

    PayOffCall payOff(strike);

    ParameterConstant rParam(r);
    ParameterConstant dParam(d);

    TreeEuropean europeanOption(expiry,payOff);
    TreeAmerican americanOption(expiry,payOff);

    BinomialTree theTree(spot, rParam, dParam, vol, steps, expiry);

    double euroPrice = theTree.getThePrice(europeanOption);
    double americanPrice = theTree.getThePrice(americanOption);
    
    std::cout << "euro price" << euroPrice << "amer price" << americanPrice << std::endl;
    
    double BSPrice = BlackScholesCall(spot, strike, r, d, vol, expiry);
    
    std::cout << "BS formula euro price" << BSPrice << std::endl;
    
    PayOffForward forwardPayOff(strike);
    TreeEuropean forward(expiry,forwardPayOff);

    double forwardPrice = theTree.getThePrice(forward);
    
    std::cout << "forward price by tree" << forwardPrice << std::endl;
    
    double actualForwardPrice = std::exp(-r*expiry)*(spot*std::exp((r-d)*expiry)-strike);
    
    std::cout << "forward price" << actualForwardPrice << std::endl;
    
    steps++; // now redo the trees with one more step
    
    BinomialTree newTree(spot,rParam,dParam,vol,steps,expiry);
    
    double euroNewPrice = newTree.getThePrice(europeanOption);
    double americanNewPrice = newTree.getThePrice(americanOption);
    
    std::cout << "euro new price" << euroNewPrice << "amer new price" << americanNewPrice << std::endl;
    
    double forwardNewPrice = newTree.getThePrice(forward);
    
    std::cout << "forward price by new tree" << forwardNewPrice << std::endl;
    
    double averageEuro = 0.5*(euroPrice+euroNewPrice);
    double averageAmer = 0.5*(americanPrice+americanNewPrice);
    double averageForward = 0.5*(forwardPrice+forwardNewPrice);
    
    std::cout << "euro av price" << averageEuro << "amer av price" << averageAmer << std::endl;
    std::cout << "av forward" << averageForward << std::endl;

    return 0;
}