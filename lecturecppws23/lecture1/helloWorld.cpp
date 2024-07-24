

#include <iostream> // header file library

int main(){ // main function is called when running code
    std::cout << "Hello World!" << std::endl;  // print "Hello World!"
    // the << says "push it" into 
    // the std::endl is needed because Lunix uses "\n" and windows "\r\n". the \r is "carrier return"
    // because the carrier return was needed with the old typewriters.  

    return 0; // return terminates the program
    // in linux: 0 is success; 1 some fail. 
    // you can also: 
//    return EXIT_SUCCESS 
}
