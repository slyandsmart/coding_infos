#include <iostream>
#include <vector>

int main(){
    std::vector<double> v{1, 2, 3};
    v[2] = 1.0;
    std::cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<std::endl;
    return 0;
}
