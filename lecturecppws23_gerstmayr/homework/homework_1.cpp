/* 
****************************************************
title:      homework 01
author:     peter manzl (c8501100)
description: 
            This file is part of the Lecture 
            "C and C++ in simulation development"
            Add two standard vectors. 
****************************************************
*/


#include <vector>
#include <cmath> // for sin
#include <iostream>


int main(){
    // intialize vectors v1 and v2 with the given values
    std::vector<float> v1 {0, 0.5, 1}; 
    std::vector<float> v2 {0, sin( float(0.1)), 1}; 

    // initialize v3 witz zeros
    std::vector<float> v3 {0,0,0}; 
    // add elements of vectors 
    v3[0] = v1[0] + v2[0]; 
    v3[1] = v1[1] + v2[1]; 
    v3[2] = v1[2] + v2[2]; 

    std::cout << "v3 = [" << v3[0] << ", " << v3[1] << ", " << v3[2] << "]" << std::endl;
    return EXIT_SUCCESS;
}

