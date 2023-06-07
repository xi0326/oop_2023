// person.cpp
# pragma once
# include "person.h"
# include "employeerole.h"
# include "passengerrole.h"
# include "airline.h"



Person::Person()
{
    this->id_number = 0;
    this->name = "";
    this->airline = nullptr;
    this->role_list.clear();
}

Person::Person(int id_number, string name)
{
    this->id_number = id_number;
    this->name = name;
    this->airline = nullptr;
    this->role_list.clear();
}

Person::Person(int id_number, string name, PersonRole& role, Airline& airline)
{
    this->id_number = id_number;
    this->name = name;
    role_list.push_back(&role);
    
    this->add_member_to_airline(airline);
}

Person::Person(int id_number, string name, PersonRole& role1, PersonRole& role2, Airline& airline)
{
    this->id_number = id_number;
    this->name = name;
    role_list.push_back(&role1);
    role_list.push_back(&role2);
    
    this->add_member_to_airline(airline);
}

string Person::get_name()
{
    return this->name;
}

void Person::add_member_to_airline(Airline& airline)
{
    this->airline = &airline;
    airline.add_member(this);
}

void Person::delete_employee_role()
{
    // delete the employee role from the role list
    for (auto iter = this->role_list.begin(); iter != this->role_list.end(); iter++)
    {
        if (typeid(*iter) == typeid(EmployeeRole*))
        {
            this->role_list.erase(iter);
            (*iter)->delete_role(); // delete the employee role and it's links
            break;
        }
    }
}

void Person::delete_passenger_role()
{
    // delete the passenger role from the role list
    for (auto iter = this->role_list.begin(); iter != this->role_list.end(); iter++)
    {
        if (typeid(*iter) == typeid(PassengerRole*))
        {
            this->role_list.erase(iter);
            (*iter)->delete_role(); // delete the passenger role and it's links
            break;
        }
    }
}
