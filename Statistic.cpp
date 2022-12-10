#include "Statistic.hpp"

StatisticMean::StatisticMean() : sum(0.0), pathsDone(0UL) {}
StatisticMoment::StatisticMoment() : sum(0.0), sum2(0.0), sum3(0.0), sum4(0.0), pathsDone(0UL) {}
StatisticVaR::StatisticVaR() : sum(0.0), worst(0.0), pathsDone(0UL) {}
Statistics::Statistics() {}

void StatisticMean::dumpOneResult(double result) {
    pathsDone++;
    sum += result;
}

void StatisticMoment::dumpOneResult(double result) {
    pathsDone++;
    sum += result;
    sum2 += result*result;
    sum3 += result*result*result;
    sum4 += result*result*result*result;
}

void StatisticVaR::dumpOneResult(double result) {
    pathsDone++;
    sum += result;
    worst = worst > result ? result : worst;
}

void Statistics::dumpOneResult(double result) {
    for(int i = 0; i < statistics.size(); i++){
        statistics[i]->dumpOneResult(result);
    }
}

std::vector<std::vector<double>> StatisticMean::getResultsSoFar() const {
    std::vector<std::vector<double>> results(1);
    results[0].resize(1);
    results[0][0] = sum / pathsDone;
    return results;
}

std::vector<std::vector<double>> StatisticMoment::getResultsSoFar() const {
    std::vector<std::vector<double>> results(1);
    results[0].resize(4);
    results[0][0] = sum / pathsDone;
    results[0][1] = sum2 / pathsDone;
    results[0][2] = sum3 / pathsDone;
    results[0][3] = sum4 / pathsDone;
    return results;
}

// If I understood how VaR works
std::vector<std::vector<double>> StatisticVaR::getResultsSoFar() const {
    std::vector<std::vector<double>> results(1);
    results[0].resize(1);
    results[0][0] = sum / pathsDone - worst;
    return results;
}

//Since each statistic returns a row vector, I will put them one below the other
std::vector<std::vector<double>> Statistics::getResultsSoFar() const {
    std::vector<std::vector<double>> results(statistics.size());
    std::vector<std::vector<double>> tmp;
    for(int i = 0; i < statistics.size(); i++){
        tmp = statistics[i]->getResultsSoFar();
        results.resize(tmp[0].size());
        for(int j = 0; j < tmp[0].size(); j++){
            results[i][j] = tmp[0][j];
        }
    }
    return results;
}

void Statistics::addStatistic(StatisticMC& statistic) {
    //Cannot pass without reference and cannot make a pointer to reference
    statistics.emplace_back(Wrapper<StatisticMC>(statistic));
}

StatisticMC* StatisticMean::clone() const {
    return new StatisticMean(*this);
}

StatisticMC* StatisticMoment::clone() const {
    return new StatisticMoment(*this);
}

StatisticMC* StatisticVaR::clone() const {
    return new StatisticVaR(*this);
}

StatisticMC* Statistics::clone() const {
    return new Statistics(*this);
}