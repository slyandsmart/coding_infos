/* 
****************************************************
title:      homework 07 (part of exercise 4)
author:     peter manzl (c8501100)
description: 
    Write a function which takes a dynamic array of type double called x as input and as
    well as an output array y. The function then stores sin(x[i]) on the output array.
    Make sure that x is copied efficiently and cannot be modified inside the function. The
    output y is available outside the function after it has been called.
****************************************************
*/


#include <vector>
#include <cmath> // for sin
#include <iostream>
#include <ctime>

// creating a new vector and returning it
std::vector<double> sin (const std::vector<double> x){
    std::vector<double> y (x.size()); 
    for (int i = 0; i < x.size(); i++){
        y[i] = sin(x[i]); 
    }

    return y; 
}

// by writing the rsult in the given vector no new memory needs to be allocated
void sin (const std::vector<double> x, std::vector<double> &y){
    for (int i = 0; i < x.size(); i++){
        y[i] = sin(x[i]); 
    }

    return; 
}

int main(){
    clock_t t_1; 
    double h = 0.1;
    int N = 3200000; 
    std::vector<double> x (N); 
    std::vector<double> y (N); 
    std::vector<double> y2 (N); 
    for (int i = 0; i < N; i++){
        x[i] = (i * h);
    }

    t_1 = clock(); 
    y = sin(x); 
    t_1 = clock() - t_1; 
    std::cout << "required time version 1: " << ((float) t_1/CLOCKS_PER_SEC) << "s." << std::endl;



    t_1 = clock(); 
    sin(x, y2);  // now calling by reference
    t_1 = clock() - t_1; 
    std::cout << "required time verion 2: " <<  ((float) t_1/CLOCKS_PER_SEC) << "s." << std::endl;
    std::cout << "first 10 elements of vector y: " << std::endl; 
    int n = y2.size(); 
    if (n > 10){
        n = 10; 
    }
    for (int i = 0; i < n; i++){
        std::cout << y2[i] << ", "; 
    }
    std::cout << "... " << std::endl; 
    return 0; 
}