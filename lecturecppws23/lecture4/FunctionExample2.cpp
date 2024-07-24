// 
#include<iostream>
#include<vector>

double add(double a, double b){
    return a + b; 
}


int main(){
    
    std::cout << add(1.2, 2.2) << std::endl; 
    std::cout << add(1, 'c') << std::endl; // will be cast to 1.0 and 99 (ASCII code for 'c')
    // after overloading this typecasting does not work!!


}