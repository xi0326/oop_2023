// specificflight.cpp
# pragma once
# include "specificflight.h"
# include "regularflight.h"
# include "employeerole.h"
# include "booking.h"


SpecificFlight::SpecificFlight() {}

SpecificFlight::SpecificFlight(RegularFlight& regular_flight, string date)
{
    this->date = date;
    this->link_to_regular_flight(regular_flight);
}

void SpecificFlight::specify_regular_flight(RegularFlight& regular_flight)
{
    this->link_to_regular_flight(regular_flight);
}

void SpecificFlight::specify_date(string date)
{
    this->date = date;
}

void SpecificFlight::link_to_regular_flight(RegularFlight& regular_flight)
{
    this->regular_flight = &regular_flight;
    regular_flight.add_specific_flight(this);
}

EmployeeRole& SpecificFlight::find_crew_member(int crew_member_id)
{
    auto it = this->crew_members.begin();
    while (it != this->crew_members.end())
    {

        if ((*it)->get_employee_id() == crew_member_id)
        {
            return **it;    // return the employee role
        }
        it++;
    }

    // if the crew member is not found, throw an exception
    throw "Crew member not found";

}

void SpecificFlight::add_link_to_booking(Booking* booking)
{
    this->booking_list.push_back(booking);
}

void SpecificFlight::add_crew_member(EmployeeRole& employee)
{
    this->crew_members.push_back(&employee);
}

void SpecificFlight::delete_crew_member(EmployeeRole& employee)
{
    auto it = this->crew_members.begin();
    while (it != this->crew_members.end())
    {
        if (*it == &employee)
        {
            this->crew_members.erase(it);
            break;
        }
        it++;
    }
}

void SpecificFlight::delete_booking(Booking& booking)
{
    auto it = this->booking_list.begin();
    while (it != this->booking_list.end())
    {
        if (*it == &booking)
        {
            this->booking_list.erase(it);
            break;
        }
        it++;
    }
}