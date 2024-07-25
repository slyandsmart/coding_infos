#include <iostream>
#include <fstream> // library to read/write data

int main(){
    std::ofstream out("result.txt"); // specify output file
    
    out<<1.0<<" "<<2.2<<std::endl;  // write values
    
    return 0;
}