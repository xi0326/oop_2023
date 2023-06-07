// regularflight.h
# pragma once
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Airline;
class SpecificFlight;

class RegularFlight
{
    public:
        RegularFlight();
        RegularFlight(string flight_number, Airline& airline);
        RegularFlight(string flight_number, Airline& airline, string time);

        string get_flight_number();
        Airline get_airline();
        void set_time(string time);
        void add_specific_flight(SpecificFlight* specific_flight);
        
    private:
        string time;
        string flight_number;
        Airline* airline;
        vector<SpecificFlight*> specific_flight_list;

        void add_flight_to_airline(Airline& airline);
};