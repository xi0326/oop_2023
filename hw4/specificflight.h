// specflight.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class EmployeeRole;
class Booking;
class Airplane;
class FlightLog;

class SpecificFlight
{
    public:
        SpecificFlight();
        void specify_airplane(Airplane& airplane);  // a1
        void create_flight_log();   // b1
        void change_airplane(Airplane& airplane1, Airplane& airplane2); // d1
        EmployeeRole& find_crew_member(string crew_member_name);    // e1
        void add_link_to_booking(Booking* booking); // c3
        void add_crew_member(EmployeeRole& employee);
        
    private:
        Airplane* airplane;
        FlightLog* flight_log;
        vector<EmployeeRole*> crew_members;
        vector<Booking*> booking_list;
};