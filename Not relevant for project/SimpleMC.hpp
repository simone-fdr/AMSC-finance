#ifndef SIMPLEMC_HPP
#define SIMPLEMC_HPP

#include "Option.hpp"
#include "Parameter.hpp"
#include "Statistic.hpp"
#include "Random.hpp"
#include "Terminator.hpp"

void monteCarlo(const VanillaOption& option, double spot, const Parameter& vol,
                      const Parameter& r, StatisticMC& gatherer, RandomBase& generator, Terminator& terminator);

void generate(RandomBase& generator, FinArray& variates, double thisSpot, double movedSpot,
              const VanillaOption& option, StatisticMC& gatherer, double discounting, double rootVariance);

#endif