// personrole.cpp
# pragma once
# include "personrole.h"
# include "booking.h"
# include "specificflight.h"

PersonRole::PersonRole() {}

PersonRole::PersonRole(string name)
{
    this->name = name;
}

string PersonRole::get_name()
{
    return this->name;
}

EmployeeRole::EmployeeRole() {}

EmployeeRole::EmployeeRole(string name, int employee_id): PersonRole(name)
{
    this->employee_id = employee_id;
}

PassengerRole::PassengerRole() {}

PassengerRole::PassengerRole(string name): PersonRole(name) {}

void PassengerRole::make_booking(SpecificFlight& flight)
{
    Booking new_booking = Booking(*this, flight);
    flight.add_link_to_booking(&new_booking);
    this->add_link_to_booking(&new_booking);
}

void PassengerRole::add_link_to_booking(Booking* new_booking)
{
    this->booking_list.push_back(new_booking);
}