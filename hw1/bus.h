// bus.h
# pragma once
#include <string>
#include <vector>
#include "person.h"

using namespace std;

// bus declaration
class Bus
{
    public:
        // constructors
        Bus();
        Bus(string schedule);

        void set_schedule(string schedule);
        string get_schedule();
        void add_passenger(Person new_passenger);
        bool is_passenger(string passenger_name);
        void print_all_passengers();

    private:
        string schedule;
        vector<Person> passengers;

};