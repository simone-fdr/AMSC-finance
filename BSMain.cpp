#include "BSMain.hpp"

int main() {
    double expiry = 1;
    double strike = 100;
    double spot = 100;
    double vol = 0.2;
    double r = 0.05;
    double d = 0.01;
    unsigned long numberOfPaths = 1 << 20; //number of printed results
    unsigned numberOfDates = 50;
    
    std::string filename = "spot-strike.csv";
    std::ofstream myFile(filename);

    //myFile << "x,y" << std::endl;
    myFile << "x,y,z" << std::endl;
    FinArray times(numberOfDates);

    for (unsigned long i=0; i < numberOfDates; i++)
        times[i] = (i+1.0)*expiry/numberOfDates;

    ParameterConstant volParam(vol); //read only
    ParameterConstant rParam(r);
    ParameterConstant dParam(d);


    auto start = std::chrono::high_resolution_clock::now();

    double final_result = 0;
    
    int thread_used;
    
    PayOffCall payOff(strike);
    PathAsian option(times, expiry, payOff);

    
    #pragma omp parallel shared(thread_used) num_threads(12)
    {
        thread_used = omp_get_num_threads();
        
        StatisticMean gatherer;

        RandomParkMiller generator(numberOfDates, omp_get_thread_num()); //to set different seeds
        AntiThetic antiGen(generator);

        ExoticBSEngine engine(option, rParam, dParam, volParam, antiGen, spot);

        engine.doSimulation(gatherer, numberOfPaths/thread_used);
        double result = gatherer.getResultSoFar();

        #pragma atomic
            final_result += result/thread_used;
    }

    //std::cout << spot << "," << strike << "," << final_result << std::endl;
    //myFile << spot << "," << strike << "," << final_result << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "The function took " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Value of result: " << final_result << std::endl;
    //std::cout << "Value of r: " << r << " Value of d: " << d << " Value of result " << results[0][0] << std::endl;
    
    return 0;
}