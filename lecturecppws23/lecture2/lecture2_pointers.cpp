#include <iostream>
#include <iomanip> 

int main(){
    double a; 
    double* p; 
    p = &a; 
    a = 0.0123456789; 
    double test1 = 0.0123456789; 
    int test2 = 123456789012;

    std::cout << "values: " << std::setprecision(16) << a << " " << *p <<  std::endl; 
    std::cout << "Adresses: " << std::setprecision(16) << &a << " " << p << std::endl; 
    printf("%f", test1);


    int i = 1; 
    int* p2 = &i; 
    std::cout << "i = " << i << std::endl; 

    *p2 += 1; 

    std::cout << "now i = " << i << std::endl; 

    int **pp2 = &p2; 
    **pp2 = 3; 
    std::cout << "now i = " << i << std::endl ; 

    std::cout << "adress pp2 is: " << &pp2 << ", adress p2 is: " << pp2 << ", adress i is: " << *pp2 << std::endl;

    /* int *i2 = 1, j2 = 2; 
     std::cout << "i + j: " << i2+j2 << std::endl; // the compiler does not let you add adress + integer
    */ 

    int i3 = 3; 
    int& r = i3; 

}