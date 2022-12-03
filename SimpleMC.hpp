#ifndef SIMPLEMC_HPP
#define SIMPLEMC_HPP
#include <Option.hpp>
#include <Parameter.hpp>

    double simpleMonteCarlo(const VanillaOption& option, double spot,
                            Parameter& vol, Parameter& r, unsigned long numberOfPaths);
#endif