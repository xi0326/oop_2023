// office.h
# pragma once
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Employee;

class Office
{
    public:
        Office();
        Office(string name);

        void set_name(string name);
        string get_name();
        void add_new_employee(Employee& new_employee);
        void print_all_employees_name();

    private:
        string name;
        vector<Employee*> employees;

};