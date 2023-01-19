#include "project/BSMain.hpp"

int main(int argc, char* argv[]) {
    // Setup
    if(argc != 2){
        std::cout << "Please execute as ./Black-Scholes #threads" << std::endl;
        return 1;
    }
    int thread_used = std::atoi(argv[1]);

    // Declaration variables

    std::vector<double> values; //expiry,strike,spot,vol,r,d
    unsigned long numberOfPaths = 1 << 20; // number of samples for Monte Carlo
    unsigned int numberOfDates = 50; // number of element of time division
    FinArray times(numberOfDates); // Array with elements of time
    
    // Variables to read input
    std::string line;
    std::string token;
    // Variable used in loop
    double final_result;

    // Input file
    std::string input_filename = "input.csv";
    std::ifstream inputFile(input_filename);

    // Output file
    std::string output_filename = "output.csv";
    std::ofstream outputFile(output_filename);

    if(!inputFile.is_open() || !outputFile.is_open()){
        std::cout << "Error while opening a file" << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<RandomBase>> generators;
    //Creates n random number generator with different seeds
    for(int i = 0; i < thread_used; i++){
        generators.emplace_back(std::make_unique<RandomParkMiller>(numberOfDates, i));
    }
    
    std::vector<AntiThetic> antiGens;
    // The AntiThetic class is just an interface.
    // Therefore the real generator needs to exists.
    // Hence we need a vector for the generators and one for AntiThetic
    for(int i = 0; i < thread_used; i++){
        antiGens.emplace_back(*generators[i]);
    }

    std::vector<std::unique_ptr<StatisticMC>> gatherers;
    // Creates n gatherers that store the means
    for(int i = 0; i < thread_used; i++){
        gatherers.emplace_back(std::make_unique<StatisticMean>());
    }

    // Main loop
    while(std::getline(inputFile, line)){
        // Inizialize the string like a stream
        std::stringstream str(line);
        values.clear();
        
        while(std::getline(str,token,',')){
            values.emplace_back(std::atof(token.c_str()));
        }

        for(int i = 0; i < 6; i++)
            std::cout << values[i] << " ";
        std::cout << std::endl;

        // Generate elements
        for (unsigned long i=0; i < numberOfDates; i++)
            times[i] = (i+1.0)*values[0]/numberOfDates;

        ParameterConstant volParam(values[3]);
        ParameterConstant rParam(values[4]);
        ParameterConstant dParam(values[5]);


        PayOffCall payOff(values[1]);
        PathAsian option(times, values[0], payOff);

        final_result = 0;
        #pragma omp parallel shared(thread_used, antiGens, values, gatherers, option, rParam, dParam, volParam, numberOfPaths) num_threads(thread_used)
        {
            thread_used = omp_get_num_threads();

            int thread_id = omp_get_thread_num();
            ExoticBSEngine engine(option, rParam, dParam, volParam, antiGens[thread_id], values[2]);


            gatherers[thread_id]->clear();
            engine.doSimulation(*gatherers[thread_id], numberOfPaths/thread_used);
            double result = gatherers[thread_id]->getResultSoFar();

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