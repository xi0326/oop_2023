// personrole.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Booking;
class SpecificFlight;

class PersonRole
{
    public:
        PersonRole();
        PersonRole(string name);
        string get_name();  // e2
        
    protected:
        string name;
};

class EmployeeRole: public PersonRole
{
    public:
        EmployeeRole();
        EmployeeRole(string name, int employee_id);
        // string get_name();  // e2

    private:
        int employee_id;
        vector<SpecificFlight*> filght_list;
};

class PassengerRole: public PersonRole
{
    public:
        PassengerRole();
        PassengerRole(string name);
        void make_booking(SpecificFlight& flight);  // c1
        void add_link_to_booking(Booking* new_booking); // c4

    private:
        vector<Booking*> booking_list;
};