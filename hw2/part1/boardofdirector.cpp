// boardofdirector.cpp
# pragma once
# include "boardofdirector.h"
# include "person.h"
# include "company.h"

BoardOfDirector::BoardOfDirector(): name(""), company(nullptr){}

BoardOfDirector::BoardOfDirector(string name, Company& company)
{
    this->name = name;
    this->company = &company;

    // link to company
    this->company->link_to_board_of_director(*this);
}

void BoardOfDirector::set_name(string name)
{
    this->name = name;
}

string BoardOfDirector::get_name()
{
    return this->name;
}

void BoardOfDirector::add_new_person(Person& new_person)
{
    this->people.push_back(&new_person);

    // link to person
    new_person.add_new_board_of_directors(*this);
}

void BoardOfDirector::print_people_name()
{
    for(auto person: this->people)
    {
        cout << person->get_name() << endl;
    }
}

void BoardOfDirector::set_company(Company& company)
{
    this->company = &company;

    // link to company
    this->company->link_to_board_of_director(*this);
}

Company BoardOfDirector::get_company()
{
    return *(this->company);
}

void BoardOfDirector::link_to_company(Company& company)
{
    this->company = &company;
}