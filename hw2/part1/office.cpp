// office.cpp
# pragma once
# include "office.h"
# include "employee.h"

Office::Office(): name(nullptr){}

Office::Office(string name): name(name){};

void Office::set_name(string name)
{
    this->name = name;
}

string Office::get_name()
{
    return this->name;
}

void Office::add_new_employee(Employee& new_employee)
{
    this->employees.push_back(&new_employee);
}

void Office::print_all_employees_name()
{
    for(auto employee: this->employees)
    {
        cout << employee->get_name() << endl;
    }
}