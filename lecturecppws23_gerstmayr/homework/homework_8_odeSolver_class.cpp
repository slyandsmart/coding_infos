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
            BUT: this time use a class for the 
            solver implementation
****************************************************
*/



#include <vector>
#include <cstddef>
#include <iostream>
#include <cmath> 
#include <ctime>
#include <fstream>

class OdeSolver{
    private: 
        clock_t time_spent; 
        float _y0; 
        float _tEnd; 
        float _h; 
        int nSteps;
        int _verboseMode = 0; 
        std::vector<std::vector<float>> data; // data is vector of vectors; 
    
    public: 
        OdeSolver();
        OdeSolver(float y0, float tEnd, float h, int verboseMode);
        // starting in C++11: constructor delegation; call another constructor with set parameters.
        OdeSolver(float y0, float tEnd, float h): OdeSolver(y0, tEnd, h, 0){} ;
        ~OdeSolver(); 

        // faster because more optimized; but: compiler may do that anyway for you...
        // OdeSolver(long data): _data(data), _publicData(data) {} //
        
        void SetData(float y0, float tEnd, float h){
            _y0 = y0;
            _tEnd = tEnd;
            _h = h; 
            nSteps = std::ceil(_tEnd / _h); // ceil --> round up to avoid missing a step...
        };
        void allocateMem(); 
        void freeMem(); 
        void PrintSettings(); // output the current settings of the solver
        void Solve();           // solve the ODE from 0 to tEnd using current stepsize and save it internally
        void Write(std::string filename); // write the previously solved data to a file // write the previously solved data to a file // write the previously solved data to a file // write the previously solved data to a file

};

OdeSolver::OdeSolver(){
    std::cout << "Warning! empty constructor OdeSolver called!"; 
}

void OdeSolver::freeMem(){
    // loop over data and free memory by resizing to 0
    for (int i = 0; i < data.size() ; i++) {
        data[i].resize(0); 
    }  
    data.resize(0);
}

OdeSolver::~OdeSolver(){
    if(_verboseMode){
        std::cout << "destructor called" << std::endl; 
    }
    freeMem();
}


OdeSolver::OdeSolver(float y0, float tEnd, float h, int verboseMode){
    // setting private variables
    _y0 = y0; 
    _tEnd = tEnd; 
    _h = h; 
    _verboseMode = verboseMode; 
    nSteps = std::ceil(_tEnd / _h); // ceil --> round up to avoid missing a step...
    if (_verboseMode){
        std::cout << "constructor OdeSolver called." << std::endl; 
        PrintSettings(); 
    }
}

void OdeSolver::PrintSettings(){
    std::cout << "solver settings set to: " << std::endl; 
    std::cout << "y0=" << _y0 << std::endl << "tEnd=" << _tEnd << std::endl << "h=" << _h << std::endl; 
}
// equation is 
// y_t = sin(y(t)) --> RHS is sin(y(t))
double RHS(double y){
    return sin(y); 
}

// call explicit Euler
double explicitEuler(double y, double dt){
    return y + dt*RHS(y); 
}


void OdeSolver::allocateMem(){
    data.resize(2); // 2 variables with nSteps+1 each
    for (int i = 0; i< 2; i++){ // allocate memory which is already known!
        data[i].resize(nSteps+1); 
    }
    data[0][0] = 0; // starting time
    data[1][0] = _y0; // starting value
}



void OdeSolver::Solve(){
    time_spent = clock(); 
    allocateMem();

//    auto data_0 = 
    for(int i = 0; i < nSteps; i++){
        //std::cout << "new step " << i << std::endl; 
        data[0][i+1] = (i+1)*_h; 
        data[1][i+1] = explicitEuler(data[1][i], _h); 
    }

    time_spent = clock() - time_spent; // time
    std::cout << "time spent: " << ((float) time_spent/CLOCKS_PER_SEC) << "seconds" << std::endl; 
}

void OdeSolver::Write(std::string filename){
    // todo: check if solver was called; otherwise writing makes no sense. 
    std::ofstream output; 
    std::cout << "writing into: " << filename << std::endl; 
    output.open(filename); // create stream into results file
    output << "# results from OdeSolverClass; author: peter manzl; " << std::endl; 
    for(int i = 0; i < nSteps+1; i++){
        output << data[0][i] << ",\t" << data[1][i] << '\n';;
    }
    output.close();
    std::ofstream myfile;
};



int main(){
    std::string filename = "ODEClassResult.txt"; 
//    std::cout << "enter starting value for ode: "; 
//    float y0 = 0;
//    std::cin >> y0; 
// 
    float y0 = 1; 
    float h = 1e-4; 
    float tEnd = 20; 
    

    OdeSolver odeSolver(y0, tEnd, h, true); 
    odeSolver.Solve(); 
    odeSolver.Write(filename);
}