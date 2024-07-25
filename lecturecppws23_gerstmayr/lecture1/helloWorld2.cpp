#include <iostream>

/* void main(int a){
    std::cout << "hello back!" << std::endl;  // print "Hello World!"
    return; 
} */

int add(int a, int b)
{
    std::cout << "integer sum = " << (a + b) << std::endl;
    return 1; 
}

void add(double a, double b)
{
    std::cout << "float sum = " << (a + b) << std::endl;
}

int main(){
    std::cout << "Hello World!" << std::endl;  // print "Hello World!"
    int a = 2; 
    add(10.2, 2.0);
    add(1, 2); 
    // main(a); 
    return 0;
}


