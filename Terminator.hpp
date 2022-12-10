#include <chrono>
#include <vector>
#include "Wrapper.hpp"

class Terminator {
    public:
    Terminator() {};
    virtual ~Terminator(){};
    virtual bool isTerminated() = 0;
    virtual Terminator* clone() const=0;
};

class TimeTerminator : public Terminator{
    public:
    TimeTerminator(double time_);
    virtual bool isTerminated();
    virtual Terminator* clone() const;
    private:
    double time;
    std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<long long int, std::ratio<1, 1000000000>>> initial_time;
};

class PathsTerminator : public Terminator{
    public:
    PathsTerminator(unsigned long numberOfpaths_);
    virtual bool isTerminated();
    virtual Terminator* clone() const;
    private:
    double numberOfPaths;
    double pathsDone;
};

class EitherTerminator : public Terminator {
    public:
    EitherTerminator();
    virtual bool isTerminated();
    virtual Terminator* clone() const;
    void addTerminator(Terminator& terminator);
    private:
    std::vector<Wrapper<Terminator>> terminators;
};