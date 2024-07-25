//2023-11-09
//Johannes Gerstmayr
//sample for lecture 6
//gcc.exe -g .\test.cpp -o .\test.exe

#include <iostream>
#include <string>

class SimpleString {
public:
    std::string data;

    // Constructor
    SimpleString(const std::string& str = "") : data(str) {}
    int Size() const {return data.size();}

    // Typical getter and setter functions:
    char Get(int i) const {return data[i];}
    void Set(int i, char c) {data[i] = c;}

    // Overload the assignment operator
    SimpleString& operator=(const SimpleString& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Overload the bracket [] operator (read)
    const char& operator[](int i) const {
        return data[i];
    }

    // Overload the bracket [] operator (reference / write)
    // this is potentially dangerous because the data pointer could change!
    char& operator[](int i) {
        return data[i];
    }

    // Overload the equality (==) operator
    bool operator==(const SimpleString& other) const {
        return data == other.data;
    }

    // Overload the + operator for string concatenation
    SimpleString operator+(const SimpleString& other) const {
        return SimpleString(data + other.data);
    }

   // Overload the * operator for string length
    int operator*(const SimpleString& other) const {
        return Size() + other.Size();
    }

   // mix int and string:
    friend int operator*(const SimpleString& left, int right) {
        return left.Size() + right;
    }
    friend int operator*(int left, const SimpleString& right) {
        return left + right.Size();
    }
    // Overload the ostream << operator
    friend std::ostream& operator<<(std::ostream& os, const SimpleString& ss) {
        os << ss.data;
        return os;
    }
};

void test();

int main() {
    SimpleString s1("Hello "), s2("World!!!");

    // Test the + operator
    SimpleString s3 = s1 + s2;
    std::cout << "s3: " << s3.data << std::endl;

    // Test the == operator
    std::cout << "s1 and s2 are equal: " << ((s1==s2) ? "true" : "false") << std::endl;

    // Test the assignment operator
    SimpleString s4;
    s4 = s1;
    std::cout << "s4: " << s4 << std::endl;

    // Test the bracket operator
    std::cout << "s1[1] " << s1[1] << std::endl;
    s1[1] = 'E';
    std::cout << "s1 now is " << s1 << std::endl;

    // Test our fancy "length" operator
    std::cout << "s1*s2: " << s1*s2 << std::endl;
    std::cout << "s1*s2*s3: " << s1*s2*s3 << std::endl;

    // potential risk with referencing:
    char& store = s1[2];  //must call ref. operator
    std::cout << "store = " << store << std::endl;
    s1 = SimpleString("A new, very long string which requires std::string to reallocate");
    std::cout << "s1[2] = " << s1[2] << ", store = " << store << std::endl;
    // ==> undefined behavior and may crash !

    // Get() / Set() functions would be safer in this context
    test();

    return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <vector>

class Triangle{
protected:
    std::vector<int> points;
public:
    Triangle(std::vector<int> pointsInit) : points(pointsInit) {}
    double Area() const { return 1.0;}
    // virtual double Area() const { return 1.0;}
};
class RightTriangle : public Triangle{
public:
    RightTriangle(std::vector<int> pointsInit) : Triangle(pointsInit) {}
    double Area() const { return 1.2 * points[0];}
    // virtual double Area() const override { return 1.2 * points[0];}
};

void test()
{
    std::vector<int> points({1,2});
    RightTriangle A(points);
    std::cout << "A:" << A.Area() << std::endl;
    std::cout << "A:Triangle: " << A.Triangle::Area() << std::endl; //only works if "public Triangle" is used

    Triangle* B = &A; //B can be either Triangle or RightTriangle
    std::cout << "B:" << B->Area() << std::endl; //calls Triangle.Area, but it is in fact a RightTriangle ...
}


// class Cell{
// public: 
//     double Area() const {return 3.14;}
// };

// class Triangle : public Cell{};

// class RightTriangle : public Triangle{};

// void test2()
// {
//     RightTriangle A;
//     std::cout << A.Area() << std::endl;
// }
