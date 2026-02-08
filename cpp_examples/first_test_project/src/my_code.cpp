#include "my_code.hpp" // Insert contents of my_code.hpp at this point.  Note use of double quotes here.

int add(int x, int y)
{
    return x + y;
}


void spinner(int spin_seconds) {
    static char const spin_chars[] = "/-\\|";
    unsigned long i, num_iterations = (spin_seconds * 10);

    for (i=0; i<num_iterations; ++i) {
        std::cout << "\r" << spin_chars[i % 4] << std::flush; // Print the current spinner character and flush the output buffer
        usleep(50000);
    }
}







// Implementation of the Person class methods
// The constructor initializes the name and age of the person using an initializer list
Person::Person(const std::string& name_init, 
                int age_init): 

        name(name_init), // Initialize the name member variable with the value of name_init
        age(age_init)
        {
            std::cout << name << " As a person created!" << std::endl;  // body code
            this-> number_of_people_created++; // Increment the static member variable to keep track of the number of people created
        } // Constructor body can be empty since we are using an initializer list

        

std::string Person::getName() const { return name; }
int Person::getAge() const { return age; }

void Person::kisses(const Person& p ) const {
    std::cout << name << " kisses " << p.getName() << "!" << std::endl;
}

void Person::shows_number_of_people_created() const {
    std::cout << "Number of people created: " << this->number_of_people_created << std::endl;
}

void Person::setAge(int new_age) {
    age = new_age;
}



