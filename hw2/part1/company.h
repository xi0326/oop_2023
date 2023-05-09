// company.h
# pragma once
# include <string>
# include <vector>
# include <iostream>

using namespace std;

// forward declaration
class BoardOfDirector;
class Employee;

// company declaration
class Company
{
    public:
        Company();
        Company(string name, BoardOfDirector& board_of_director);

        void set_name(string name);
        void set_board_of_director(BoardOfDirector& board_of_director);
        string get_name();
        BoardOfDirector get_board_of_director();
        void add_new_employee(Employee& new_employee);
        void print_all_employees_name();

        void link_to_board_of_director(BoardOfDirector& board_of_director);
        // void link_to_employee(Employee& new_employee);
        
        
    private:
        string name;
        BoardOfDirector* board_of_director;
        vector<Employee*> employees;



};