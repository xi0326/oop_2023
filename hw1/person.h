// person.h
# pragma once
#include <string>

using namespace std;

// person declaration
class Person
{
    public:
        // constructors
        Person();
        Person(string name, string phone_number, string sex);

        void set_name(string name);
        void set_phone(string phone_number);
        void set_sex(string sex);
        string get_name();
        string get_phone();
        string get_sex();

    private:
        string name;
        string phone_number;
        string sex;
};
