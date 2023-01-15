#include <cmath>
#include <iostream>

// Method that uses the templates and iterates the Newton method until convergence
template<class T, double (T::*value)(double) const, double (T::*derivative)(double) const >
double NewtonRaphson(double target, double start, double tolerance, const T& object) {
    double y = (object.*value)(start);
    double x = start;
    while (std::fabs(y - target) > tolerance) {
        double d = (object.*derivative)(x);
        if(d)
            x += (target - y) / d;
        else
            break; //It is numerically unstable
        y = (object.*value)(x);
    }
    std::cout << "Tolerance achieved: " << std::fabs(y - target) << std::endl;
    return x;
}
