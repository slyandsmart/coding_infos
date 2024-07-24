// 
#include<iostream>
#include<vector>

double add(double a, double b){
    return a + b; 
}

int add(int a, int b){
    return a + b; 
}
// +, * etc. will put both datatypes to the same type; 

int main(){
    std::cout << typeid(add(1, 2)).name() << std::endl; 
    std::cout << typeid(add(1.0, 2.0)).name() << std::endl; 
    std::cout << add(1.0, 2.0) << std::endl; 
    std::vector<double> v {1.12,2.2,3.9}; 
    for (auto& i : v){ // iterates over vector v... 
        std::cout << i << std::endl; 
    }
// you can write type interfaces for classes using overloading; 
// IMPORTANT: only C++, not C. 
// y function void foo(); can be created without declaring it; 
// the compiler will then not complain and the linker has to handle that. 


}