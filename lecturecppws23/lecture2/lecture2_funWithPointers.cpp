#include <iostream>
#include <vector>
#include <algorithm> 

int main(){
    std::vector<int> v {0, 1,2,3,4};
    std::cout << "v :"; 
    for(const& i : v){
        std::cout << i << ", "; 
    }
    std::cout << std::endl; 
    
    
    std::remove_if(v.begin(), v.end(), [](const int& i){return i % 2 == 0;});
    
    std::cout << "v :"; 
    for(const& i : v){
        std::cout << i << ", "; 
    }
    std::cout << std::endl; 
    // all_of, none_of and all these functions from the algorithms are extremely helpful; 
    // there is a lot of functionality alraedy implemented. Do NOT reinvent the wheel. 
}