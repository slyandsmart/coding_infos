#include <vector>
#include <iostream>
#include <string>


class Reference {
public:
    Reference()                 { std::cout << "Default constructor" << std::endl; }
    Reference(const Reference&) { std::cout << "Default copy-constructor" << std::endl; }
    Reference(Reference&&)      { std::cout << "Default move-constructor" << std::endl; }

    Reference& operator=(const Reference&)      { std::cout << "Default copy-assignment-operator" << std::endl; return *this; }
    Reference& operator=(Reference&&) noexcept  { std::cout << "Default move-assignment-operator" << std::endl; return *this; }
};

class A : public Reference {
public:
    void doStuff() { std::cout << "A::doStuff() : " << c << std::endl; }
    std::string c = "X";
};

class B : public Reference {
public:
    void doStuff() { std::cout << "B::doStuff() : " << c << std::endl; }
    int c = 0;
};

// helper function to print std::vector<>
template <typename T>
void printVec(const std::vector<T>& vec, const std::string& name) {
    std::cout << name << " : ";
    for(const auto& elem : vec){
        std::cout << "\"" << elem << "\" ";
    }
    std::cout << std::endl;
}

int main() {

    std::vector<int> tmp {1,2,3,4,5,6,7,8,9};

    printVec(tmp);
    tmp.erase(tmp.end()-2,tmp.end());
    printVec(tmp);

    exit();
    
    std::cout << "       Type A" << std::endl << std::endl;
    std::cout << "construct some elements" << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;

    A a;
    a.doStuff();
    a.c = "a";
    a.doStuff();

    A b(a);
    b.doStuff();
    b.c = "b";
    b.doStuff();
    
    A c(std::move(b));
    c.doStuff();
    b.doStuff();

    std::cout << "-----------------------" << std::endl << std::endl;
    std::cout << "assign some elements" << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;

    A d,e;
    d.c = "d";
    e.c = "e";
    
    d.doStuff();
    d = a;
    d.doStuff();
    a.doStuff();

    std::cout << "-----------------------" << std::endl;
    
    e.doStuff();
    e = std::move(a);
    e.doStuff();
    a.doStuff();

    std::cout << "-----------------------" << std::endl << std::endl << std::endl;

    std::cout << "       Type B" << std::endl << std::endl;
    std::cout << "construct some elements" << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;

    B f;
    B h(std::move(f));
    h.doStuff();
    f.doStuff();

    std::cout << "-----------------------" << std::endl << std::endl;
    std::cout << "assign some elements" << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;

    B j;
    j.c = 5;
    j.doStuff();
    j = std::move(h);
    j.doStuff();
    f.doStuff();

    std::cout << "-----------------------" << std::endl;

    return EXIT_SUCCESS;
}