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
    
    private:
        PassengerRole* passenger;
        SpecificFlight* flight;
};