// passengerrole.h
# pragma once
# include "personrole.h"

using namespace std;


class PassengerRole: public PersonRole
{
    public:
        PassengerRole();
        Booking& make_booking(SpecificFlight& flight);  // c1
        void add_link_to_booking(Booking* new_booking); // c4
        void delete_booking(Booking& booking);
        
        // @ override
        void delete_role();

    private:
        vector<Booking*> booking_list;
};