#ifndef SIMPLEMC_HPP
#define SIMPLEMC_HPP

#include "Option.hpp"
#include "Parameter.hpp"
#include "Statistic.hpp"
#include "Random.hpp"

void simpleMonteCarlo(const VanillaOption& option, double spot, const Parameter& vol, 
                      const Parameter& r, unsigned long numberOfPaths, StatisticMC& gatherer, RandomBase& generator);

#endif