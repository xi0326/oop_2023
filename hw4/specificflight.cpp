// specificflight.cpp
# pragma once
# include "specificflight.h"
# include "personrole.h"
# include "booking.h"
# include "airplane.h"
# include "flightlog.h"


SpecificFlight::SpecificFlight() {}

void SpecificFlight::specify_airplane(Airplane& airplane)
{
    this->airplane = &airplane;
    airplane.add_link_to_specific_flight(this);
}

void SpecificFlight::create_flight_log()
{
    FlightLog new_flight_log = FlightLog(*this);
}

// change the airplane from airplane1 to airplane2
void SpecificFlight::change_airplane(Airplane& airplane1, Airplane& airplane2)
{
    this->airplane = &airplane2;
    airplane1.delete_link_to_specific_flight(this);
    airplane2.add_link_to_specific_flight(this);
}

EmployeeRole& SpecificFlight::find_crew_member(string crew_member_name)
{
    auto it = this->crew_members.begin();
    while (it != this->crew_members.end())
    {

        if ((*it)->get_name() == crew_member_name)
        {
            return **it;    // return the employee
        }
        it++;
    }
}

void SpecificFlight::add_link_to_booking(Booking* booking)
{
    this->booking_list.push_back(booking);
}

void SpecificFlight::add_crew_member(EmployeeRole& employee)
{
    this->crew_members.push_back(&employee);
}