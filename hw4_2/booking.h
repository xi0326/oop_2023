// booking.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class PassengerRole;
class SpecificFlight;


class Booking
{
    public:
        Booking();
        Booking(PassengerRole& passenger, SpecificFlight& flight);  // c2
        void cancel_booking();
    
    private:
        PassengerRole* passenger;
        SpecificFlight* flight;
};