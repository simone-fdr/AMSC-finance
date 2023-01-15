#include "project/BSMain.hpp"

int main() {
    std::vector<double> values; //expiry,strike,spot,vol,r,d
    unsigned long numberOfPaths = 1 << 20;
    unsigned int numberOfDates = 50;
    std::string line;
    std::string token;
    FinArray times(numberOfDates);

    std::string input_filename = "input.csv";

    std::ifstream inputFile(input_filename);

    // OUTPUT
    std::string output_filename = "output.csv";
    std::ofstream outputFile(output_filename);

    if(!inputFile.is_open() || !outputFile.is_open()){
        std::cout << "Error while opening a file" << std::endl;
        return 1;
    }
    
    while(std::getline(inputFile, line)){

        std::stringstream str(line);
        values.clear();
        
        while(std::getline(str,token,',')){
            values.emplace_back(std::atof(token.c_str()));
        }

        for(int i = 0; i < 6; i++)
            std::cout << values[i] << " ";
        std::cout << std::endl;

        for (unsigned long i=0; i < numberOfDates; i++)
            times[i] = (i+1.0)*values[0]/numberOfDates;

        ParameterConstant volParam(values[3]);
        ParameterConstant rParam(values[4]);
        ParameterConstant dParam(values[5]);

        double final_result = 0;
        
        int thread_used;
        
        PayOffCall payOff(values[1]);
        PathAsian option(times, values[0], payOff);

        #pragma omp parallel shared(thread_used) num_threads(12)
        {
            thread_used = omp_get_num_threads();
            
            StatisticMean gatherer;

            RandomParkMiller generator(numberOfDates, omp_get_thread_num()); //to set different seeds
            AntiThetic antiGen(generator);

            ExoticBSEngine engine(option, rParam, dParam, volParam, antiGen, values[2]);

            engine.doSimulation(gatherer, numberOfPaths/thread_used);
            double result = gatherer.getResultSoFar();

            #pragma atomic
                final_result += result/thread_used;
        }
        
        outputFile  << values[0] << ',' 
                    << values[1] << ','
                    << values[2] << ',' 
                    << values[3] << ','  
                    << values[4] << ',' 
                    << values[5] << ',' 
                    << final_result << std::endl;
        std::cout << final_result << std::endl;
    }
    return 0;
}