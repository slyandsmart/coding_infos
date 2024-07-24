#include <vector>
#include <iostream>
#include <string>

void printVec(const std::vector<std::string>& vec, const std::string& name) {
    std::cout << name << " : ";
    for(const auto& elem : vec){
        std::cout << "\"" << elem << "\" ";
    }
    std::cout << std::endl;
}

int main(){

    // initialization
    
    std::vector<std::string> a; // creates an empty vector of type std::string
    std::vector<std::string> b {"a", "a,b", "a,b,c", "a,b,c,d"};

    // access

    std::cout << "at    : " << b.at(1) << std::endl;
    std::cout << "[]    : " << b[2] << std::endl;

    std::cout << "front : " << b.front() << std::endl;
    std::cout << "back  : " << b.back() << std::endl;

    std::cout << std::endl << std::endl;

    // useful member functions

    std::cout << "a.empty() : " << a.empty() << std::endl;
    std::cout << "b.empty() : " << b.empty() << std::endl;

    std::cout << "a.size() : " << a.size() << std::endl;
    std::cout << "b.size() : " << b.size() << std::endl;

    std::cout << std::endl << std::endl;

    // iterators

    std::cout << "b -> forward iter  : ";
    for(auto i = b.begin(); i != b.end(); ++i){
        std::cout << "\"" << *i << "\" ";
    }
    std::cout << std::endl;
    
    std::cout << "b -> backward iter : ";
    for(auto i = b.rbegin(); i != b.rend(); ++i){
        std::cout << "\"" << *i << "\" ";
    }
    std::cout << std::endl << std::endl;

    // add/remove elements

    printVec(b, "b");
    b.erase(b.begin());
    printVec(b, "b");
    b.erase(b.begin(), b.begin()+2); // this version is removing the range [begin(), begin()+1]
    printVec(b, "b");
    b.clear();
    printVec(b, "b");

    b.push_back("z");
    b.emplace_back("z,y");
    printVec(b, "b");

    b.insert(b.end(), "z,y,x,w,v");
    printVec(b, "b");
    b.insert(b.begin()+2, "z,y,x");
    printVec(b, "b");
    b.emplace(b.end()-1, "z,y,x,w");
    printVec(b, "b");
    b.pop_back();
    printVec(b, "b");
    
    std::cout << std::endl;

    return EXIT_SUCCESS;
}