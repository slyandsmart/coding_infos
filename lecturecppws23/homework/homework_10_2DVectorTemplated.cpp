#include <iostream>
#include <array>
#include <stdexcept> //for std::out_of_range
#include <cmath> 
#include <string> 
#include <typeinfo>

template  <class vecType> 
            class Vector2D {
private:
    vecType data[2]; //simpler, but does not allow move-semantics
    //std::array<double, 2> data;
    /*template <typename U>
        friend Vector2D<decltype(vecType() + U())> operator+(const Vector2D<vecType>& v1, const Vector2D<U>& v2);
        */
public:
    //Parameterized constructor
    Vector2D(vecType x, vecType y) : data{x, y} {
        // std::cout << "type of vector: " << typeid(data[0]).name() << std::endl;
        }

    //Copy constructor
    Vector2D(const Vector2D& other) {
        data[0] = other.data[0];
        data[1] = other.data[1];
    }

    // 
    vecType GetX() const {return data[0];}; 
    vecType GetY() const {return data[1];}; 
    
    double Norm(){
        return sqrt(data[0] * data[0] + data[1] * data[1]);
    };
    //Move constructor
    //Vector2D(Vector2D&& other) = default; //simplest
    //Vector2D(Vector2D&& other) noexcept : data(std::move(other.data)) {} //only for std::array

    //Equality operator
    bool operator==(const Vector2D& other) const {
        return (data[0] == other.data[0] && data[1] == other.data[1]);
    }

    //Inequality operator
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }

    //Addition operator
    Vector2D operator+(const Vector2D<vecType>& other) const {
        return Vector2D(data[0] + other.data[0], data[1] + other.data[1]);
    }
    
    /*//Addition operator
    Vector2D operator+(const Vector2D<double>& other) const {
        return Vector2D(data[0] + other.data[0], data[1] + other.data[1]);
    }
*/
    

    //unitary Subtraction operator
    Vector2D operator-(const vecType& other) const {
        return Vector2D(data[0] - other, data[1] - other);
    }

    //Subtraction operator for double
    Vector2D operator-(const Vector2D<double>& other) const {
        return Vector2D(data[0] - other.data[0], data[1] - other.data[1]);
    }
    //Subtraction operator for int
    Vector2D operator-(const Vector2D<int>& other) const {
        return Vector2D(data[0] - other.data[0], data[1] - other.data[1]);
    }
/*
    //Multiplication vector with vector
    Vector2D operator*(const Vector2D<double>& other) const {
        return Vector2D(data[0] * other.data[0], data[1] * other.data[1]);
    }*/
    Vector2D operator*(const Vector2D<vecType>& other) const {
        return Vector2D(data[0] * other.data[0], data[1] * other.data[1]);
    }

    //overloading Multiplication operator with scalar multiplication
    Vector2D operator*(const vecType& other) const {
        return Vector2D(data[0] * other, data[1] * other);
    }
    

    //Subscript operator for const and non-const objects
    vecType& operator[](int index) {
        if (index < 0 || index >= 2) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const vecType& operator[](int index) const {
        if (index < 0 || index >= 2) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    //A friend function for outputting the Vector2D
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        return os << '[' << v.data[0] << ", " << v.data[1] << ']';
    }
    
    // using another template to enable operations between Vector2D<vecType> and Vecot2D<vecType2>
    template <typename vecType2>
    Vector2D<decltype(vecType() + vecType2())> operator+(const Vector2D<vecType2>& other) const {
        return Vector2D<decltype(vecType() + vecType2())>(data[0] + other.GetX(), data[1] + other.GetY());
    }

    template <typename vecType2>
    Vector2D<decltype(vecType() - vecType2())> operator-(const Vector2D<vecType2>& other) const {
        return Vector2D<decltype(vecType() - vecType2())>(data[0] - other.GetX(), data[1] - other.GetY());
    }

    template <typename vecType2>
    Vector2D<decltype(vecType() * vecType2())> operator*(const Vector2D<vecType2>& other) const {
        return Vector2D<decltype(vecType() * vecType2())>(data[0] * other.GetX(), data[1] * other.GetY());
    }

};


int main() {
    Vector2D<double> vec1(1.0, 2.5);
    Vector2D<double> vec2(3, 4);
    Vector2D<int> vec2_int(3, 4);

    Vector2D<double> vec3 = vec1 + vec2;
    Vector2D<double> vec4 = vec1 - vec2;
    Vector2D<double> vec4_1 = vec1 * vec2;
    Vector2D<double> vec4_2 = vec2 * 2;
    Vector2D<double> vec5(0,0); 
    vec5 = vec2 + vec2_int; 
    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << ", |vec2|: "  << vec2.Norm() << std::endl;
    std::cout << "vec3 = vec1 + vec2: " << vec3 << std::endl;
    std::cout << "vec4 = vec2 - vec1: " << vec4 << std::endl;
    std::cout << "vec4_1 = vec1 * vec2: " << vec4_1 << std::endl;
    std::cout << "vec4_2  = vec2 * 2: " << vec4_2 << std::endl; 
  //  std::cout << "vec4_2 (vec2 * 2 ) - 2: " << vec4_2 - 2 << std::endl; 
    std::cout << "vec1 == vec2: " << (vec1 == vec2 ? "true" : "false") << std::endl;
    std::cout << "vec1[0]: " << vec1[0] << std::endl;


    std::cout << "Operating on different types of vectors: " << std::endl;
    std::cout << "vec5 = vec2<double>  + vec2<int> : " << vec5 << " == 2*vec2 : " << vec2*2 <<std::endl;
    
    return 0;
}
