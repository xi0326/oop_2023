// booking.cpp
# pragma once
# include "booking.h"
# include "passengerrole.h"
# include "specificflight.h"

Booking::Booking() {}

Booking::Booking(PassengerRole& passenger, SpecificFlight& flight)
{
    this->passenger = &passenger;
    this->flight = &flight;
    flight.add_link_to_booking(this);
    passenger.add_link_to_booking(this);
}

void Booking::cancel_booking()
{
    this->passenger->delete_booking(*this);
    this->flight->delete_booking(*this);
}