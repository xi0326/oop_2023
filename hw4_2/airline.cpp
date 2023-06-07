// airline.cpp
# pragma once

# include "airline.h"
# include "person.h"
# include "regularflight.h"

Airline::Airline()
{
    this->name = "";
    this->member_list.clear();
}

Airline::Airline(string name)
{
    this->name = name;
    this->member_list.clear();
}

string Airline::get_name()
{
    return this->name;
}

void Airline::add_member(Person* person)
{
    this->member_list.push_back(person);
}

void Airline::add_flight(RegularFlight* flight)
{
    this->flight_list.push_back(flight);
}