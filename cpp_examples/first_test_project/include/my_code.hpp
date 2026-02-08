// We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

#include <iostream>
// Add some header guards to prevent multiple inclusions of this header file
# pragma once
// This is the content of the .h file, which is where the declarations go
int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!


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



