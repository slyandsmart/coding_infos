
#include <iostream> // header file library
#include <fstream> 
#include <cmath> 
#include <vector>

int main(){ // main function is called when running code
    std::ofstream out("restult.txt");
    out << "1 + 2.0 = " << 1 + 2.0 << std::endl;
    std::cout << "created output file results.txt " << std::endl;
    double tmp1, tmp2; 
    std::string tmp3;

    std::fstream in("input.txt");
    in >> tmp1; 
    in >> tmp2; 
    in >> tmp3; 
    
    std::cout << "tmp1: '" << tmp1 << "', tmp2: '" << tmp2 <<"', tmp3: '" << tmp3 << "'" << std::endl;  // print "Hello World!"
    int sum = int(tmp1) + tmp2; 

    std::cout << "sum = " << sum << std::endl; 
    //std::string test; 
    if (false) {
        char test; 
        std::cin >> test; 
        std::cout << test << " was entered." << std::endl; 
        // this streaming operator can also be used for classes; 
        // also append, add etc. can also be used for data there. 
    }    


    // setting up a vector with an arbitrary size can take 1000s of clock cycles
    // cppreference.com is a good source for the definitions.
    std::vector<double> vectorTest{1.0, 2.0, 5.0, 8.4}; 
    std::cout << vectorTest[0]; 

    char a = char(int(50));
    char strTest[12] = "abcdefghijk"; 
    std::cout << a << ", strTest: " << strTest << std::endl;

    const int n = 42; 
    return 0; // return terminates the program
}
