//2023-11-09
//Johannes Gerstmayr
//sample for lecture 6
//gcc.exe -g .\test.cpp -o .\test.exe

#include <initializer_list>
#include <vector>
#include <iostream>

class D {
public:
    std::vector<int> values;
    //old school:
    //D(x): values({x}) {}
    //D(x, y): values({x,y}) {}
    D(std::initializer_list<int> list) : values(list) {}
};

int main() {
    D d = {1, 2, 3, 4, 5}; // Initializer list constructor
    D e({13, 42});
    std::string sep = "";
    std::cout << "\nd:";
    for (int v : d.values) 
    {
         std::cout << sep << v;
         sep = ", ";
    }
    std::cout << "\ne:";
    sep = "";
    for (int v : e.values) 
    {
         std::cout << sep << v;
         sep = ", ";
    }
}
