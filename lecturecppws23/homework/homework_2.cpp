/* 
****************************************************
title:      homework 01
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
            till monday 16.10. 
****************************************************
*/


#include <vector>
#include <cmath> // for sin
#include <iostream>
#include <fstream> 
#include <ctime>

double y_t(double y){
    return sin(y); 
}

double euler(double y, double dt){
    return y + dt*y_t(y);
}


int main(){
    clock_t time_req; 
    time_req = clock(); 
    std::ofstream resultsFile("results.txt"); // create stream into results file
    const double dt = 1e-2;             // declaring const enables better optimization for compiler
    const double y0 = 0.5;              // initial value 
    const int nSteps = 100;             // dt*nSteps = 1 second
    std::vector<double> y (nSteps+1);   // n steps + initial value
    y[0] = y0;  // assign initial value

    resultsFile << "# explicit euler integration of y_t = sin(y(t))" << std::endl; // write header in numpy style
    resultsFile << "time; value" << std::endl;

    resultsFile << 0 << ";" << y[0] << std::endl;
    for (int i = 1; i <= nSteps; i++){
        y[i] = euler(y[i-1], dt); 
        resultsFile << i*dt << ";" << y[i] << std::endl;
    }
    std::cout << "explicit euler, y_t = sin(y) "  << std::endl;
    std::cout << "t= " << dt*nSteps << ", y= " << y[nSteps] << std::endl; 
    std::cout << "max size of y: " << y.capacity() << std::endl; 
    
    time_req = clock() - time_req;
    std::cout << "function took: " << (float)time_req/CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;

}