// employee.cpp
# pragma once
# include "employee.h"
# include "company.h"
# include "office.h"

Employee::Employee(): name(nullptr), company(nullptr), office(nullptr){}

Employee::Employee(string name, Company& company, Office& office)
{
    this->name = name;
    this->company = &company;
    this->office = &office;

    // link to company and office
    this->company->add_new_employee(*this);
    this->office->add_new_employee(*this);
}

void Employee::set_name(string name)
{
    this->name = name;
}

void Employee::join_company(Company& company)
{
    this->company = &company;
    this->company->add_new_employee(*this);
}

void Employee::set_office(Office& office)
{
    this->office = &office;
    this->office->add_new_employee(*this);
}

string Employee::get_name()
{
    return this->name;
}

Company Employee::get_company()
{
    return *(this->company);
}

Office Employee::get_office()
{
    return *(this->office);
}