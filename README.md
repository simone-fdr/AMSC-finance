# Black-Scholes

## Abstract

This program exploits the stochastic nature of the market and tries to estimate the theoretical value of an option over time.

The program reads an input file "input.csv" and for each value read it calculates the average of the value over time of the Asian option.

Outside the scope of the parallized section are declared all the variables that can be shared.

Then the parallel section of the code run and the result is calculated.

At the end the code outputs the result in "output.csv".

## Short description

Let 'n' be the number of thread used

Initially the main declares some variables like the number of sample

Then declares an array of n random number generators with different seeds

Followed by an array of n antithetic generators to wrap up the random number generators

And an array of n gatherers that will hold the information

After reading the input it will initialize the necessary parameters

Then it will create an engine that can simulate the Black-Scholes market model

The Monte Carlo simulation is run in parallel among the thread and the final result is the mean of the results of the various threads

## How to test

Use the command "make" to compile the program

The "input.csv" file that has been already provided

In case one would create its own input file there is a Python script (both in .py and .ipynb format) that create the input with preferred input values ranges

The source file of the main project is BSMain.cpp and all the other files are inside the project folder.

The NewtonMain.cpp file is not compiled nor used and it is included only to show a different approach to the problem.

The files have LF endings in order to be compatible with Unix systems