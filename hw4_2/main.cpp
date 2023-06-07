// main.cpp
# pragma once
# include "airline.h"
# include "booking.h"
# include "employeerole.h"
# include "passengerrole.h"
# include "person.h"
# include "regularflight.h"
# include "specificflight.h"

int main()
{
    // create airline
    Airline starlux = Airline("STARLUX Airlines");
    Airline jal = Airline("JAPAN AIRLINES");

    // create flights
    RegularFlight JX800 = RegularFlight("JX800", starlux, "08:30");
    RegularFlight JX803 = RegularFlight("JX803", starlux, "16:10");
    RegularFlight JL096 = RegularFlight("JL096", jal, "09:10");
    RegularFlight JL809 = RegularFlight("JL809", jal, "18:10");

    // search flights
    // starlux.search_flight("JX800");

    // create specific flights
    SpecificFlight JX800_20230603 = SpecificFlight(JX800, "2023-06-03");
    SpecificFlight JX803_20230610 = SpecificFlight(JX803, "2023-06-10");
    SpecificFlight JL096_20230604 = SpecificFlight(JL096, "2023-06-04");
    SpecificFlight JL809_20230610 = SpecificFlight(JL809, "2023-06-10");

    // create person roles
    EmployeeRole employee_role1 = EmployeeRole(1);  // supervisor
    EmployeeRole employee_role2 = EmployeeRole(2, employee_role1);  // subordinate
    EmployeeRole employee_role3 = EmployeeRole(3);  // supervisor

    PassengerRole passenger_role1 = PassengerRole();
    PassengerRole passenger_role2 = PassengerRole();
    PassengerRole passenger_role3 = PassengerRole();

    // create persons
    Person person1 = Person(1, "John", employee_role1, passenger_role1, starlux);   // John is a supervisor and a passenger of STARLUX Airlines
    Person person2 = Person(2, "Mary", employee_role2, passenger_role2, starlux);   // Mary is a subordinate and a passenger of STARLUX Airlines
    Person person3 = Person(3, "Peter", employee_role3, jal);      // Peter is a supervisor of JAPAN AIRLINES
    Person person4 = Person(4, "Tom", passenger_role3, jal);       // Tom is a passenger of JAPAN AIRLINES

    // create bookings
    Booking booking1 = passenger_role1.make_booking(JX800_20230603);
    Booking booking2 = passenger_role1.make_booking(JX803_20230610);
    Booking booking3 = passenger_role2.make_booking(JX800_20230603);
    Booking booking4 = passenger_role2.make_booking(JL809_20230610);
    Booking booking5 = passenger_role3.make_booking(JL096_20230604);

    // delete bookings
    passenger_role1.delete_booking(booking2);
    passenger_role3.delete_booking(booking5);
    


    return 0;
}