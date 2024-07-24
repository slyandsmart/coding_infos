

#include <iostream>
#include <vector>
#include <array> 

class A{
    public:
    double* _d;
    A(double d): _d(new double) {*_d = d;}
    ~A() {delete _d;}
    A(const A& a){ 
        // with the copy constructor it now works!! 
        _d = new double, 
        *_d = *a._d;  // without the new you will just get a seg fault
        // the standard constructor would use _d = a._d; 

    }
};

class B{
    private: 
        std::array<double, 3> data; 
    public: 
        B(std::array<double, 3> _data): {
            data = _data };   

};

void foo(A aFoo){
    // foo creates a copy of A and copies the pointer; 
    // at the end of this function the destructor is called
    // for the copy but also frees the memory from the original instance of A. 
}

int main(){
    A a(1.234);
    {
        double x = 3.14;
        A a2(x); 

    }
    foo(a);
    std::cout<< *a._d <<std::endl;
}
