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
        virtual void delete_role() = 0;

};