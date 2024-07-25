/* 
****************************************************
title:      homework 05
author:     peter manzl (c8501100)
description: 
            This file is part of the Lecture 
            "C and C++ in simulation development"
            implement the forward euler

            y(0) = 0.5
            y_t = sin(y(t))
            dt = 0.01
            y_n1 = yn + (dt)
            output into csv format
            time; result; \n
            0; 0.5; \n 
            0.01; y2; \n ...
            BUT: now use functions (RHS)
****************************************************
*/


#include <vector>
#include <cmath> // for sin
#include <iostream>
#include <fstream> 

// equation is 
// y_t = sin(y(t)) --> RHS is sin(y(t))
double RHS(double y){
    return sin(y); 
}

// call explicit Euler
double explicitEuler(double y, double dt){
    return y + dt*RHS(y); 
}

double ODESolver(double y0, double nSteps, double dt, bool flagDebug){
    std::ofstream resultsFile("results.txt"); // create stream into results file
    std::vector<double> y (nSteps+1);   // n steps + initial value
    y[0] = y0;  // assign initial value
    
    resultsFile << "# explicit euler integration of y_t = sin(y(t))" << std::endl; // write header in numpy style
    resultsFile << "time; value" << std::endl;

    resultsFile << 0 << ";" << y[0] << std::endl;
    for (int i = 1; i <= nSteps; i++){
        y[i] = explicitEuler(y[i-1], dt); 
        resultsFile << i*dt << ";" << y[i] << std::endl;
    }
    
    if (flagDebug){
        std::cout << "explicit euler, y_t = sin(y) "  << std::endl;
        std::cout << "t= " << dt*nSteps << ", y= " << y[nSteps] << std::endl; 

    }
    
    return 0.0; 
}

int main(){
    const double dt = 1e-2;             // declaring const enables better optimization for compiler
    const double y0 = 0.5;              // initial value 
    const int nSteps = 100;             // dt*nSteps = 1 second

    ODESolver(y0, nSteps, dt, true);  // call solver
    
    return 0;

}