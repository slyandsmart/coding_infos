/* 
****************************************************
title:      homework 01
author:     peter manzl (c8501100)
description: 
            This file is part of the Lecture 
            "C and C++ in simulation development"
            write a program which gets an arbitrary number as an input and
            as an output write if the number is an integer or a floating point number. 
            note: you do not need to use switch case, other ways are okay too!  
****************************************************
*/


#include <cmath> 
#include <iostream>

int main(){
    // std::string input;    
    double input; 
    std::cout << "Please enter an arbitrary number." << std::endl; 
    std::cin >> input; 
    std::cout << "input: '" << input <<"' was read. " << std::endl;

    if (std::fmod(input, 1.0) == 0 || (input - int(input) == 0) ){
        std::cout << "This is an integer." << std::endl; 
    }
    else{
        std::cout << "This is a double." << std::endl; 
    }
    
    /*else{
        std::cout << "did not recognice the input type as a double or integer. " << std::endl; 
    }*/

}