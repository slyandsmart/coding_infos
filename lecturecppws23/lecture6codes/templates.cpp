//2023-11-09
//Johannes Gerstmayr
//sample for lecture 6
//gcc.exe -g .\test.cpp -o .\test.exe

#include <iostream>
#include <string>


template <typename T>
T foo( T a, T b ){
    return a+b;
}

// note: there is also std::swap !
template <class T>
inline void Swap(T & a, T & b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T max(const T& a, const T& b){
    if( a > b) { return a; }
    else { return b; }
}


int main() {
    {
        double a=1, b=42;
        double out = foo<double>(a, b);

        std::cout << out << "\n";
        Swap(a,b);
        std::cout << a << "," << b << "\n";
    }
    {
        double a = 0.1, b = 1.3;
        double c = max<double>(a,b);
        double c2 = max(a,b); //compiler knows, it is double!
        std::cout << c << std::endl;
        int d = 1;
        double e = max<int>(b,d); //casts to int!
        //double e = max(a,d); //does not compile
        std::cout << e << std::endl;
    }

}
