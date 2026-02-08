// We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

#include <iostream>
#include <unistd.h>


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


// Add some header guards to prevent multiple inclusions of this header file
# pragma once
// This is the content of the .h file, which is where the declarations go
int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!
void spinner(int spin_seconds); 


class Person
{
    private:
        const std::string name;
        int age;
        int number_of_people_created = 0; // member variable to keep track of the number of people created

    public:
        Person(const std::string& name, int age);
        std::string getName() const; // const member function to get the name of the person, which does not modify the state of the object
        int getAge() const;     // const member function to get the age of the person, which does not modify the state of the object
        void setAge(int new_age); // member function to set the age of the person, which modifies the state of the object

        void kisses(const Person& p ) const;
        void shows_number_of_people_created() const;
};



