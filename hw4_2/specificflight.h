// specflight.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class EmployeeRole;
class Booking;
class RegularFlight;

class SpecificFlight
{
    public:
        SpecificFlight();
        SpecificFlight(RegularFlight& regular_flight, string date);
        void specify_regular_flight(RegularFlight& regular_flight);
        void specify_date(string date);
        EmployeeRole& find_crew_member(int crew_member_id);    // e1
        void add_link_to_booking(Booking* booking); // c3
        void add_crew_member(EmployeeRole& employee);
        void delete_crew_member(EmployeeRole& employee);
        void delete_booking(Booking& booking);
        
    private:
        string date;
        RegularFlight* regular_flight;
        vector<EmployeeRole*> crew_members;
        vector<Booking*> booking_list;

        void link_to_regular_flight(RegularFlight& regular_flight);
};