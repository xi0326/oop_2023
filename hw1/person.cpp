// person.cpp
# pragma once
#include "person.h"
// default constructor
Person::Person(): name(nullptr), phone_number(nullptr), sex(nullptr){}

// constructor wiooth name, phone_number and sex
Person::Person(string name, string phone_number, string sex):
    name(name), phone_number(phone_number), sex(sex){}

void Person::set_name(string name)
{
    this->name = name;
}

void Person::set_phone(string phone_number)
{
    this->phone_number = phone_number;
}

void Person::set_sex(string sex)
{
    this->sex = sex;
}

string Person::get_name()
{
    return this->name;
}

string Person::get_phone()
{
    return this->phone_number;
}

string Person::get_sex()
{
    return this->sex;
}