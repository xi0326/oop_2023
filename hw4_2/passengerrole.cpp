// passengerrole.cpp
# include "passengerrole.h"
# include "specificflight.h"
# include "booking.h"

PassengerRole::PassengerRole() {}

// PassengerRole::PassengerRole(string name): PersonRole(name) {}

Booking& PassengerRole::make_booking(SpecificFlight& flight)
{
    static Booking new_booking = Booking(*this, flight);    // static variable for returning reference
    flight.add_link_to_booking(&new_booking);
    this->add_link_to_booking(&new_booking);

    return new_booking;
}

void PassengerRole::add_link_to_booking(Booking* new_booking)
{
    this->booking_list.push_back(new_booking);
}

void PassengerRole::delete_booking(Booking& booking)
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

void PassengerRole::delete_role()
{
    for (auto booking: this->booking_list)
    {
        booking->cancel_booking();
    }
}