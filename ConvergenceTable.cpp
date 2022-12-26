#include "ConvergenceTable.hpp"

ConvergenceTable::ConvergenceTable(const Wrapper<StatisticMC>& inner_): inner(inner_) {
    stoppingPoint=99999999;
    pathsDone=0;
}

StatisticMC* ConvergenceTable::clone() const {
    return new ConvergenceTable(*this);
}

void ConvergenceTable::dumpOneResult(double result) {
    inner->dumpOneResult(result);
    pathsDone++;
    if (pathsDone == stoppingPoint) {
        stoppingPoint+=999999999;
        std::vector<std::vector<double>> thisResult(inner->getResultsSoFar());
        for (unsigned long i=0; i < thisResult.size(); i++) {
            thisResult[i].push_back(pathsDone);
            resultsSoFar.push_back(thisResult[i]);
        }
    }
    return;
}

std::vector<std::vector<double>> ConvergenceTable::getResultsSoFar() const {
    std::vector<std::vector<double>> tmp(resultsSoFar);
    if (pathsDone+999999999 != stoppingPoint) {
        std::vector<std::vector<double>> thisResult(inner->getResultsSoFar());
        for (unsigned long i=0; i < thisResult.size(); i++) {
        thisResult[i].push_back(pathsDone);
        tmp.push_back(thisResult[i]);
        }
    }
    return tmp;
}