//2023-11-09
//Johannes Gerstmayr
//sample for lecture 6
//gcc.exe -g .\test.cpp -o .\test.exe

#include <iostream>
#include <string>
#include <utility>

class A {
public:
    std::string s;
    int k;
    A() : s("test"), k(-1) {}
    A(const A& o) : s(o.s), k(o.k) { std::cout << "move failed!\n"; }
    A(A&& o) noexcept:             // important for optimizer / std lib
        s(std::move(o.s)),          // explicit move of a member of class type
        k(std::exchange(o.k, 0)) {} // explicit move of a member of non-class type
};

A f(A a) //function usually copies A when returning a
{ 
    return a; 
} 

int main()
{
    std::cout << "Trying to move A\n";
    A a1 = f(A()); // return by value move-constructs the target from the function parameter
    std::cout << "first: a1.k = " << a1.k << '\n';
    A a2 = std::move(a1); // move-constructs from xvalue
    std::cout << "now:   a1.k = " << a1.k << '\n';
}