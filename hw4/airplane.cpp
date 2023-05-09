// airplane.cpp
# pragma once
# include "airplane.h"
# include "specificflight.h"

Airplane::Airplane() {}

Airplane::Airplane(string model)
{
    this->model = model;
}

void Airplane::add_link_to_specific_flight(SpecificFlight* flight)
{
    this->flight_list.push_back(flight);
}

void Airplane::delete_link_to_specific_flight(SpecificFlight* flight)
{
    // find the which the flight need to be deleted
    auto it = find(this->flight_list.begin(), this->flight_list.end(), flight);

    // if the element is found, delete it
    if (it != this->flight_list.end())
        this->flight_list.erase(it);
}

string Airplane::get_model()
{
    return this->model;
}