// company.cpp
# pragma once
# include "company.h"
# include "employee.h"
# include "boardofdirector.h"


Company::Company(): name(""), board_of_director(nullptr){}

Company::Company(string name, BoardOfDirector& board_of_director)
{
    this->name = name;
    this->board_of_director = &board_of_director;

    // link to board_of_firector
    this->board_of_director->link_to_company(*this);
}

void Company::set_name(string name)
{
    this->name = name;
}

void Company::set_board_of_director(BoardOfDirector& board_of_director)
{
    this->board_of_director = &board_of_director;

    // link to board_of_firector
    this->board_of_director->link_to_company(*this);
}

string Company::get_name()
{
    return this->name;
}

BoardOfDirector Company::get_board_of_director()
{
    return *(this->board_of_director);
}

void Company::add_new_employee(Employee& new_employee)
{
    this->employees.push_back(&new_employee);
}

void Company::print_all_employees_name()
{
    for(auto employee: this->employees)
    {
        cout << employee->get_name() << endl;
    }
}

void Company::link_to_board_of_director(BoardOfDirector& board_of_director)
{
    this->board_of_director = &board_of_director;
}