// person.cpp
# pragma once
# include "person.h"
# include "boardofdirector.h"

Person::Person(): name(nullptr){}

Person::Person(string name): name(name){}

void Person::set_name(string name)
{
    this->name = name;
}

string Person::get_name()
{
    return this->name;
}

void Person::add_new_board_of_directors(BoardOfDirector& new_board_of_director)
{
    this->board_of_directors.push_back(&new_board_of_director);
}

void Person::print_all_board_of_directors_name()
{

    for(auto board_of_director: this->board_of_directors)
    {
        cout << board_of_director->get_name() << endl;
    }
}