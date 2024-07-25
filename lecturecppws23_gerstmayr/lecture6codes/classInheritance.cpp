//2023-11-23
//Johannes Gerstmayr
//inheritance example
//gcc.exe -g .\test.cpp -o .\test.exe

#include <vector>
#include <iostream>

class Triangle{
private:
    std::vector<int> points;
public:
    Triangle(std::vector<int> pointsInit) : points(pointsInit) {}
    double Area()const{ return 1.0;}
    void Print() const
    {
        std::string sep = "";
        for (auto p: points)
        {
            std::cout << sep << p;
            sep = ",";
        }
        std::cout << "\n";
    }
};

class RightTriangle : public Triangle{
public:
    RightTriangle(std::vector<int> pointsInit) : Triangle(pointsInit) {}
    int Hypotenuse()const{ return 1;}
};

int main() 
{
    std::vector<int> points = {1,2,3}; 
    RightTriangle A(points);
    std::cout << "Triangle:";
    A.Print();
    std::cout << std::endl;
    std::cout << A.Area() << std::endl;
}
