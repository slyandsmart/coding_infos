#include <cstddef>
#include <iostream>
#include "Entry.h"


/*struct Entry{
    long data;
    Entry* next;
    Entry* previous;
};
*/


// this is how you can implement the class function not inside the class definition but outside
// the PrintNicely is defined in the Entry Function
void Entry::PrintNicely(){
    std::cout << "Data entry: " << _data << std::endl; 
}

// when implmenting functions in the .h file it is faster when running because the compiler duplicates the assembler code and 
// Eigen is a header only liary; does not have any cpp files
class myList{
    private: 
        Entry* firstElement; 
        Entry* lastElement;     //
    public: 
        void addEntry(double number){
            
        };
        void getEntry(int i){

        }
        // 
}; 


class Entry2{
    public: 
        Entry2(double* dataPtr): _data( dataPtr){};
        double* _data; 
        /* ~Entry2() {
            delete _data; // can not deletedhere ... 
        }; */
};

// Johannes: funtions, structures, etc. start with a big letter! 
// variables starting with _ are often used to only access 
int main (){
    Entry first(2); 
    first.print(); 
    first.set(4); 
    first.print(); 
 
    double data = 2; 
    Entry2 tmp(&data); 
    data = 3.1415; 
    std::cout << *tmp._data << std::endl; 
    return 0;
}


/* 
    * the const qualifier adds safety (do not change accidently) and may increase performance
    * in large code: either use const/non-const or do not care about it at all; 
    * mutable: lets you break the rule of const locally; be very careful with that --> but may be sometimes neccesarry
    * example slides 5, List (slide 35 etc.) --> 
          * allocation should be only done at one place; maybe even using a function! also: check if you got the memory, so that
          * when you run out of memory you know it where it happened ...
          * if last == NULL: not initialized yet ...
          * 
*/