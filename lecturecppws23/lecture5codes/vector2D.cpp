#include <iostream>
#include <array>
#include <stdexcept> //for std::out_of_range

class Vector2D {
private:
    double data[2]; //simpler, but does not allow move-semantics
    //std::array<double, 2> data;

public:
    //Default constructor
    Vector2D() : data{0.0, 0.0} {}

    //Parameterized constructor
    Vector2D(double x, double y) : data{x, y} {}

    //Copy constructor
    Vector2D(const Vector2D& other) {
        data[0] = other.data[0];
        data[1] = other.data[1];
    }

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
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(data[0] + other.data[0], data[1] + other.data[1]);
    }

    //Subtraction operator
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(data[0] - other.data[0], data[1] - other.data[1]);
    }

    //Subscript operator for const and non-const objects
    double& operator[](int index) {
        if (index < 0 || index >= 2) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const double& operator[](int index) const {
        if (index < 0 || index >= 2) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    //A friend function for outputting the Vector2D
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        return os << '(' << v.data[0] << ", " << v.data[1] << ')';
    }
};

int main() {
    Vector2D vec1(1.0, 2.0);
    Vector2D vec2(3.0, 4.0);

    Vector2D vec3 = vec1 + vec2;
    Vector2D vec4 = vec2 - vec1;
    
	Vector2D vec5(); //defines a new function vec5() which returns a Vector2D
    Vector2D vec6{}; //calls default constructor
    Vector2D vec7;

    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    std::cout << "vec3 (vec1 + vec2): " << vec3 << std::endl;
    std::cout << "vec4 (vec2 - vec1): " << vec4 << std::endl;
    std::cout << "vec1 == vec2: " << (vec1 == vec2 ? "true" : "false") << std::endl;
    std::cout << "vec1[0]: " << vec1[0] << std::endl;

    std::cout << "vec5: " << vec5 << std::endl;
    std::cout << "vec6: " << vec6 << std::endl;
    std::cout << "vec7: " << vec7 << std::endl;

    return 0;
}
