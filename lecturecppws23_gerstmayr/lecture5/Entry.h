

class Entry{
    private: 
        long _data; 
        Entry* _next; 
        Entry* _previous; 
    public: 
    // constructor: does not have a return type. 
        Entry(long data): _data(data) {}
        void print(){
            std::cout << _data << std::endl; 
        };
        void set(long data){
            _data = data; 
        }
        void PrintNicely();  // print in a nicer way with the comment
};