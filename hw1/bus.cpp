// bus.cpp
# pragma once
#include <iostream>
#include "person.h"
#include "bus.h"

// default constructor
Bus::Bus(): schedule(nullptr){}

// construtor
Bus::Bus(string schedule): schedule(schedule){}

void Bus::set_schedule(string schedule)
{
    this->schedule = schedule;
}

string Bus::get_schedule()
{
    return this->schedule;
}

// add new passenger to the bus
void Bus::add_passenger(Person new_passenger)
{
    this->passengers.push_back(new_passenger);
}

// print out all the passengers in the bus
void Bus::print_all_passengers()
{
    auto iterator = this->passengers.begin();

    // if there is no passenger booked the bus
    if (iterator == this->passengers.end())
    {
        cout << "There's no any passenger booked the " << this->get_schedule() << " bus." << endl;
    }
    else
    {
        cout << "These passengers have booked the bus at " << this->get_schedule() << endl;
        // through the passenger vector
        while (iterator != this->passengers.end())
        {
            cout << iterator->get_name() << endl;
            iterator++;
        }
    }
}

bool Bus::is_passenger(string passenger_name)
{
    for (auto p : this->passengers)
    {
        if (p.get_name() == passenger_name)
        {
            return true;
        }
    }
    
    return false;
}