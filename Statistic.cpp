#include "Statistic.hpp"

StatisticMean::StatisticMean() : sum(0.0), pathsDone(0UL) {}

void StatisticMean::dumpOneResult(double result) {
    pathsDone++;
    sum += result;
}

std::vector<std::vector<double>> StatisticMean::getResultsSoFar() const {
    std::vector<std::vector<double>> results(1);
    results[0].resize(1);
    results[0][0] = sum / pathsDone;
    return results;
}

StatisticMC* StatisticMean::clone() const {
    return new StatisticMean(*this);
}