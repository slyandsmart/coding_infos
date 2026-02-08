// Hello world example in C++

#include <iostream>
#include "my_code.hpp" // Insert contents of my_code.hpp at this point.  Note use of double quotes here.
#include <string_view>

// Printout collors https://medium.com/@vitorcosta.matias/print-coloured-texts-in-console-a0db6f589138
#define ESC "\033["
#define LIGHT_BLUE_BKG "106"
#define RED_BKG "101"
#define WHITE_BKG "7"
#define GREEN_TXT "32"
#define RED_TXT "31"
#define PURPLE_TXT "35"
#define WHITE_TXT "0"
#define RESET "\033[m"

int main() {

    std::cout << std::endl; // Print a newline for better readability of the output
    std::cout << ESC << RED_TXT << ";" << WHITE_BKG <<"m"<< "Hello, world!" << RESET << std::endl;
    std::cout << "Hello, World! This is a simple C++ program." << std::endl;

    std::cout << "Standard output and simple function in C++." << std::endl<< std::endl;
    std::cout << "2 + 3 = " << add(2, 3) << std::endl; // Call the add function defined in my_code.hpp

    std::cout << "Creating some Person objects and demonstrating their functionality. To show Class usage." << std::endl;
    Person alice("Alice", 30);
    alice.shows_number_of_people_created();    
    Person bob("Bob", 25);
    bob.shows_number_of_people_created();

    alice.kisses(bob); // Call the kisses method of the Person class

    alice.setAge(31); // Update Alice's age using the setAge method
    std::cout << alice.getName() << " is now " << 
                                alice.getAge() << 
                                " years old." << std::endl; // Call the getName and getAge methods to display Alice's updated age





    return 0;
}




