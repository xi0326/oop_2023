// flightlog.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class SpecificFlight;

class FlightLog
{
    public:
        FlightLog();
        FlightLog(SpecificFlight &flight);  // b2
        void write_log(string data);
        string get_log();
        
    private:
        string log_data;
        SpecificFlight* flight;
};