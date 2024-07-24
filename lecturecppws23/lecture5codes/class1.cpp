#include <iostream> // header file library 2 3 

class Entry{
private:
    long _data;
    Entry* _next;
    Entry* _previous;
public:
    long _publicData;
    Entry(long data): _data(data), _publicData(data) {}
    void Print() {std::cout << "_data=" << _data << "\n";}
};


int main()
{
    Entry first(2);
    //std::cout<<first._data;
    first.Print();
    std::cout << "first._publicData=" << first._publicData << "\n";

    return 0; // return terminates the program
}


