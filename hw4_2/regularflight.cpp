// regularflight.cpp
# pragma once
# include "regularflight.h"
# include "airline.h"

RegularFlight::RegularFlight()
{
    this->time = "";
    this->flight_number = "";
    this->airline = NULL;
}

RegularFlight::RegularFlight(string flight_number, Airline& airline)
{
    this->time = "";
    this->flight_number = flight_number;
    
    this->add_flight_to_airline(airline);
}

RegularFlight::RegularFlight(string flight_number, Airline& airline, string time)
{
    this->time = time;
    this->flight_number = flight_number;
    
    this->add_flight_to_airline(airline);
}

string RegularFlight::get_flight_number()
{
    return this->flight_number;
}

Airline RegularFlight::get_airline()
{
    return *(this->airline);
}

void RegularFlight::set_time(string time)
{
    this->time = time;
}

void RegularFlight::add_flight_to_airline(Airline& airline)
{
    this->airline = &airline;
    airline.add_flight(this);
}

void RegularFlight::add_specific_flight(SpecificFlight* specific_flight)
{
    this->specific_flight_list.push_back(specific_flight);
}