// booking_system.h
# pragma once
#include "person.h"
#include "bus.h"

using namespace std;

// booking system declaration
class BookingSystem
{
    public:
        void booking();
        void print_booking_details();
        void inquiry();
        void system_test();
        
    private:
        // initialise the buses
        Bus bus_morning = Bus("morning");
        Bus bus_afternoon = Bus("afternoon");
};