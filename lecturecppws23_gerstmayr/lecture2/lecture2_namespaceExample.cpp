
#include <iostream>

namespace manzpe{
    void foo(){
        std::cout << "manzpe::foo was called!" << std::endl; 
    }
    
}


int main(){
    
    manzpe::foo(); 
    int x = 2; 
    for (int i = 0; i < 10; i++){
        x += i; 
        std::cout << x << ", ";
        int y = x*2;
    }

    std::cout << x << ", ";
    
    return EXIT_SUCCESS; 
}