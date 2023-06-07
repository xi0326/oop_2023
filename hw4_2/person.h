// person.h
# pragma once
# include <string>
# include <vector>

using namespace std;

// forward declaration
class PersonRole;
class Airline;


class Person
{
    public:
        Person();
        Person(int id_number, string name);
        Person(int id_number, string name, PersonRole& role, Airline& airline);
        Person(int id_number, string name, PersonRole& role1, PersonRole& role2, Airline& airline);

        string get_name();  // e2
        void add_member_to_airline(Airline& airline);
        void delete_employee_role();
        void delete_passenger_role();

    private:
        int id_number;
        string name;
        vector<PersonRole*> role_list;
        Airline* airline;
};
