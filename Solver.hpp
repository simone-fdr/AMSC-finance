template<class T>
double Bisection(double target, double low, double high, double tolerance, T function) {
    double x=0.5*(low+high);
    double y=function(x);
    do {
        if (y < target)
        low = x;
        if (y > target)
        high = x;
        x = 0.5*(low+high);
        y = function(x);
    } while ((fabs(y-target) > tolerance) );
    return x;
}

template<class T, double (T::*value)(double) const, double (T::*derivative)(double) const>
double NewtonRaphson(double target, double start, double tolerance, const T& object) {
    double y = (object.*value)(start);
    double x=start;
    while (fabs(y - target) > tolerance) {
        double d = (object.*derivative)(x);
        x+= (target-y)/d;
        y = (object.*value)(x);
    }
    return x;
}
