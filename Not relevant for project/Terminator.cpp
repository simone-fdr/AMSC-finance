#include "Terminator.hpp"

EitherTerminator::EitherTerminator() {}

TimeTerminator::TimeTerminator(double time_) : time(time_), initial_time(std::chrono::steady_clock::now()) {}

PathsTerminator::PathsTerminator(unsigned long paths_) : numberOfPaths(paths_) , pathsDone(0) {}

bool TimeTerminator::isTerminated(){
    auto now = std::chrono::steady_clock::now();
    double elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds> (now - initial_time).count();
    return elapsed_time > time;
}

bool PathsTerminator::isTerminated(){
    return (pathsDone++) > numberOfPaths;
}

void EitherTerminator::addTerminator(Terminator& terminator) {
    terminators.emplace_back(Wrapper<Terminator>(terminator));
}

bool EitherTerminator::isTerminated(){
    for(int i = 0; i < terminators.size(); i++)
        if(terminators[i]->isTerminated()) 
            return true;
    return false;
}

Terminator* TimeTerminator::clone() const {
    return new TimeTerminator(*this);
}

Terminator* PathsTerminator::clone() const {
    return new PathsTerminator(*this);
}

Terminator* EitherTerminator::clone() const {
    return new EitherTerminator(*this);
}