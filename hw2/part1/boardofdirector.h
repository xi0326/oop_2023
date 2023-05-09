// boardofdirector.h
# pragma once
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Company;
class Person;

class BoardOfDirector
{
    public:
        BoardOfDirector();
        BoardOfDirector(string name, Company& company);
        void set_name(string name);
        string get_name();
        void add_new_person(Person& new_person);
        void print_people_name();
        void set_company(Company& company);
        Company get_company();

        void link_to_company(Company& company);

    private:
        string name;
        Company *company;
        vector<Person*> people;
};