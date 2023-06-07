// airline.h
# pragma once
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Person;
class RegularFlight;

class Airline
{
    public:
        Airline();
        Airline(string name);

        string get_name();
        void add_member(Person* person);
        void add_flight(RegularFlight* flight);

    private:
        string name;
        vector<Person*> member_list;
        vector<RegularFlight*> flight_list;
};