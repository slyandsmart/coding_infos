#include <iostream>
#include <string>


struct Pair{
    double first; 
    double second; 
}; 

class myClass{
    public: 
        std::string myName; 
        void printNameAndValues(){
            std::cout << "my Name is: " << myName; 
        }; 

};


int main(){
    Pair p; 
    p.first = 1.0; 
    p.second = 2.0; 

    std::cout << "first value: " << p.first << ", second value: " << p.second << std::endl;
}

