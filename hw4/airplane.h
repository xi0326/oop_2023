// airplane.h
# pragma once
# include <iostream>
# include <string>
# include <vector>
# include <algorithm>

using namespace std;

// forward declaration
class SpecificFlight;

class Airplane
{
    public:
        Airplane();
        Airplane(string model);
        void add_link_to_specific_flight(SpecificFlight* flight);   // a2, d3
        void delete_link_to_specific_flight(SpecificFlight* flight);    // d2
        string get_model();

    private:
        string model;
        vector<SpecificFlight*> flight_list;
};