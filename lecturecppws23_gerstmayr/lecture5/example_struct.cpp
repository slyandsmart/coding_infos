#include <cstddef>
#include <iostream>


struct entry{
    long data;
    entry* next;
    entry* previous;
};

int main (){
    entry* previous= NULL;
    long nEntries = 10; 
    for( long i = 0; i < nEntries; ++i ){
        // create sequence of number and fill up with integers starting with 0
        entry* current = new entry;
        current ->data = i;
        current ->previous = previous;
        if(previous) previous ->next = current;
        previous = current;
        }
    previous ->next = NULL;
    
    std::cout << "reverse order: " << std::endl;
    entry * current = previous; 
    while(current -> previous){ // traverse backwards by 
        std::cout << current->data<<std::endl; 
        current = current->previous;
    }
    std::cout << current->data<<std::endl; 
    

    // evaluation of (current -> next) returns false when it is NULL
    std::cout << "traversing forward: " << std::endl;
    while(current -> next){ // traverse forward
        std::cout << current->data<<std::endl; 
        current = current->next;
    }
    std::cout << current->data<<std::endl; 

    
    return 0;
}