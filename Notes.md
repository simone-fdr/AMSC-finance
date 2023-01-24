# Readme and compiling
Readme is clear. Project compiles and run with no issues. Shows nice scalability.

# Code

* In `NewtonRaphson` `template<class T, double (T::*value)(double) const, double (T::*derivative)(double) const >` is not necessary to be this specific in the templates, this is just verbose. If you want to force the class `T` to have a certain method you may use concepts (but they were not part of the course).

* In BSMain.cpp
`#pragma atomic -> #pragma omp atomic`  This error is bad. Unfortunately, if you do not activate the warnings this directive is ignored and no message are produced by g++ or clang++.


- `const T* const operator->() const` -> qualifiers in return type are useless. It's not an error, just redundant: `T* const operator->() const` is enough

- In constructor `CashFlow::CashFlow(long unsigned int, double)` you have a warning if you activate warnings. The reason is the the order of initialization in the initializer list does not corrispond to the order of member variables in the class declaration. Not a problem in your case, but remember that member variables are initialized ALWAYS in the order they appear in the declaration. 
- `RandomBase` is an abstract class, so it will be used as base class of a polymorphic family. So, it should have a virtual destructor!
 
- Another warning returned if you use `-Wall -Wextra`
 project/Parameter.cpp:70:18: warning: comparison of integer expressions of different signedness: `int` and `std::vector<double>::size_type` {aka `long unsigned int`} [-Wsign-compare]
   70 |     for(i = 0; i < points.size(); i++){
   Is not a problem here, but declaring vector indexes `std::size_t` solves the problem.

* `FinArray` could use `std::vector` as a member to avoid managing raw memory pointers


In conclusion, good programming with some stupid errors that could have been avoided compiling with full warnings (as suggested during lectures!).
