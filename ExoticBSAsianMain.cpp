#include "ParkMiller.hpp"
#include <iostream>
#include "Statistic.hpp"
#include "ConvergenceTable.hpp"
#include "AntiThetic.hpp"
#include "Path.hpp"
#include "ExoticEngine.hpp"
#include <string>
#include <fstream>

int main() {
    double expiry = 1;
    double strike = 10;
    double spot = 9;
    double vol = 2;
    double r = 0.05;
    double d = 0.01;
    unsigned long numberOfPaths = 1 << 18; //number of printed results
    unsigned numberOfDates = 50;
    
    std::string filename = "strike-spot.csv";
    std::ofstream myFile(filename);

    myFile << "x,y,z <- titles" << std::endl;

    for(strike = 1; strike < 10; strike++){
    for(spot = 1; spot < 10; spot++){

        PayOffCall payOff(strike);
        FinArray times(numberOfDates);

        for (unsigned long i=0; i < numberOfDates; i++)
            times[i] = (i+1.0)*expiry/numberOfDates;
    


        ParameterConstant volParam(vol);
        ParameterConstant rParam(r);
        ParameterConstant dParam(d);

        PathAsian option(times, expiry, payOff);
        
        StatisticMean gatherer;

        ConvergenceTable convTable(gatherer);
        RandomParkMiller generator(numberOfDates);
        AntiThetic antiGen(generator);

        ExoticBSEngine engine(option, rParam, dParam, volParam, antiGen, spot);
        engine.doSimulation(convTable, numberOfPaths);
        std::vector<std::vector<double>> results = convTable.getResultsSoFar();

        /*std::cout <<"\nFor the Asian call price the results are \n";
        std::cout <<"\nVol value for this iteration is: " << vol << std::endl;
        for (unsigned long i=0; i < results.size(); i++) {
            for (unsigned long j=0; j < results[i].size(); j++) {
                std::cout << results[i][j] << " ";
            }
            std::cout << "\n";
        }
        */
        std::cout << "Value of strike: " << strike << " Value of spot: " << spot << " Value of result " << results[0][0] << std::endl;
        myFile << strike << "," << spot << "," << results[0][0] << std::endl;

        }
    }
    return 0;
}