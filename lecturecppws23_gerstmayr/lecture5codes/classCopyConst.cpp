//2023-11-09
//Johannes Gerstmayr
//sample solution for lecture 5
//gcc.exe -g .\test.cpp -o .\test.exe

#include <iostream>
class A
{
public:
    double* _d;
    A(double d): _d(new double) {*_d = d;}
    //A(const A& a): _d(new double) {*_d = *(a._d);}
    ~A() {delete _d;}
};

void foo(A aFoo){}
//void foo(const A& aFoo){}

int main()
{
    A a(1.234);
    foo(a);
    std::cout<< *a._d <<std::endl;
}