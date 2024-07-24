#include <iostream>

int main(){
    double inputInt;
    double inputDouble;
    std::cout<<"Enter two numbers: Integer ";
    std::cin >> inputInt;
    std::cout<<", Double ";
    std::cin >> inputDouble;
    double sum = inputInt + inputDouble;
    std::cout<<"sum is "<<sum<<std::endl;
    return 0;
}
