#include "ParkMiller.hpp"
#include <iostream>
#include "Statistic.hpp"
#include "ConvergenceTable.hpp"
#include "AntiThetic.hpp"
#include "Path.hpp"
#include "ExoticEngine.hpp"
#include <string>
#include <fstream>
#include <chrono>
#include <omp.h>

int main() {
    double expiry = 1;
    double strike = 10;
    double spot = 9;
    double vol = 2;
    double r = 0.05;
    double d = 0.01;
    unsigned long numberOfPaths = 1 << 18; //number of printed results
    unsigned numberOfDates = 50;
    
    //std::string filename = "strike-spot.csv";
    //std::ofstream myFile(filename);

    //myFile << "x,y,z" << std::endl;
    FinArray times(numberOfDates);

    for (unsigned long i=0; i < numberOfDates; i++)
        times[i] = (i+1.0)*expiry/numberOfDates;


    ParameterConstant volParam(vol); //readonly
    ParameterConstant rParam(r);
    ParameterConstant dParam(d);


    auto start = std::chrono::high_resolution_clock::now();

    double final_result = 0;
    
    int thread_used;
    
    PayOffCall payOff(strike);
    PathAsian option(times, expiry, payOff);

    
    
    #pragma omp parallel shared(thread_used) num_threads(4)
    {
        thread_used = omp_get_num_threads();
        
        StatisticMean gatherer;
        //ConvergenceTable convTable(gatherer);

        RandomParkMiller generator(numberOfDates, omp_get_thread_num()); //to seed different seeds
        AntiThetic antiGen(generator);
        

        ExoticBSEngine engine(option, rParam, dParam, volParam, antiGen, spot);

        engine.doSimulation(gatherer, numberOfPaths/thread_used);
        double result = gatherer.getResultSoFar();

        #pragma critical
        {
            std::cout << result << std::endl;
            final_result += result;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "The function took " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Value of result: " << final_result/thread_used << std::endl;

    /*std::cout <<"\nFor the Asian call price the results are \n";
    std::cout <<"\nVol value for this iteration is: " << vol << std::endl;
    for (unsigned long i=0; i < results.size(); i++) {
        for (unsigned long j=0; j < results[i].size(); j++) {
            std::cout << results[i][j] << " ";
        }
        std::cout << "\n";
    }
    */
    //std::cout << "Value of r: " << r << " Value of d: " << d << " Value of result " << results[0][0] << std::endl;
    //myFile << r << "," << d << "," << results[0][0] << std::endl;
    return 0;
}