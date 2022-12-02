#include <Random.hpp>
#include <SimpleMC.hpp>
#include <iostream>
#include <cmath>

double SimpleMonteCarlo(const PayOff& payOff, double expiry, double spot,
                        double vol, double r, unsigned long numberOfPaths){
    double variance = vol*vol*expiry;
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5*variance;
    double movedSpot = Spot*std::exp(r*expiry + itoCorrection);
    double spot;
    double sum=0;
    for (unsigned long i=0; i < NumberOfPaths; i++){
        double gaussian = GetOneGaussianByBoxMuller();
        spot = movedSpot*std::exp(rootVariance*gaussian);
        double payOff = PayOff(spot);
        sum += payOff;
    }
    double mean = sum / numberOfPaths;
    mean *= exp(-r*expiry);
    return mean;
}


int main(){
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPaths;
    std::cout << "\nEnter expiry\n";
    std::cin >> Expiry;
    std::cout << "\nEnter strike\n";
    std::cin >> Strike;
    std::cout << "\nEnter spot\n";
    std::cin >> Spot;
    std::cout << "\nEnter vol\n";
    std::cin >> Vol;
    std::cout << "\nr\n";
    std::cin >> r;
    std::cout << "\nNumber of paths\n";
    std::cin >> NumberOfPaths;

    PayOff callPayOff(Strike, PayOff::call);
    PayOff putPayOff(Strike, PayOff::put);

    double resultCall = SimpleMonteCarlo(callPayOff, Expiry, Strike, Spot,
                                        Vol, r, NumberOfPaths);

    double resultPut = SimpleMonteCarlo(putPayOff, Expiry, Strike, Spot,
                                        Vol, r, NumberOfPaths);

    std::cout <<"the price is " << result << std::endl;
    double tmp;
    std::cin >> tmp;
    return 0;
}