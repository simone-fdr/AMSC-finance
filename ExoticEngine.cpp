#include "ExoticEngine.hpp"

ExoticEngine::ExoticEngine(const Wrapper<Path>& product_, const Parameter& r_) :
            product(product_), r(r_), discounts(product_->possibleCashFlowTimes()) {
    for (unsigned long i=0; i < discounts.size(); i++)
        discounts[i] = exp(-r.integral(0.0, discounts[i]));
    vectCashFlows.resize(product->maxNumberOfCashFlows());
}

void ExoticEngine::doSimulation(StatisticMC& gatherer, unsigned long numberOfPaths) {
    FinArray spotValues(product->getLookAtTimes().size());
    vectCashFlows.resize(product->maxNumberOfCashFlows());
    double thisValue;
    for (unsigned long i =0; i < numberOfPaths; ++i) {
        getOnePath(spotValues);
        thisValue = doOnePath(spotValues);
        gatherer.dumpOneResult(thisValue);
    }
    return;
}

double ExoticEngine::doOnePath(const FinArray& spotValues) const {
    unsigned long numberFlows = product->cashFlows(spotValues, vectCashFlows);
    double value=0.0;
    //#pragma omp parallel for reduction(+:value) useless since I'm already using all my processors in parallel
    for (unsigned i =0; i < numberFlows; ++i)
        value += vectCashFlows[i].amount * discounts[vectCashFlows[i].timeIndex];
    return value;
}

void ExoticBSEngine::getOnePath(FinArray& spotValues) {
    generator->getGaussians(variates);
    double currentLogSpot = logSpot;
    for (unsigned long j=0; j < numberOfTimes; j++) {
        currentLogSpot += drifts[j];
        currentLogSpot += standardDeviations[j]*variates[j];
        spotValues[j] = std::exp(currentLogSpot);
    }
    return;
}

ExoticBSEngine::ExoticBSEngine(const Wrapper<Path>& product_, const Parameter& r_, const Parameter& d_,
    const Parameter& vol_, const Wrapper<RandomBase>& generator_, double spot_) :
    ExoticEngine(product_ ,r_), generator(generator_) {
    FinArray times(product_->getLookAtTimes());
    numberOfTimes = times.size();
    generator->resetDimensionality(numberOfTimes);
    drifts.resize(numberOfTimes);
    standardDeviations.resize(numberOfTimes);
    double variance = vol_.integralSquare(0,times[0]);
    drifts[0] = - r_.integral(0.0,times[0]) + d_.integral(0.0, times[0]) - 0.5 * variance;
    standardDeviations[0] = std::sqrt(variance);
    for (unsigned long j=1; j < numberOfTimes; ++j) {
        double thisVariance =
        vol_.integralSquare(times[j-1],times[j]);
        drifts[j] = - r_.integral(times[j-1],times[j]) + d_.integral(times[j-1],times[j]) - 0.5 * thisVariance;
        standardDeviations[j] = std::sqrt(thisVariance);
    }
    logSpot = std::log(spot_);
    variates.resize(numberOfTimes);
}