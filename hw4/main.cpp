// main.cpp
# pragma once
# include "airplane.h"
# include "booking.h"
# include "flightlog.h"
# include "personrole.h"
# include "specificflight.h"

int main()
{

    // make two different airplanes
    Airplane airplane1 = Airplane("Airbus A380");
    Airplane airplane2 = Airplane("Boeing 787");

    // make a specific flight
    SpecificFlight flight1 = SpecificFlight();
    SpecificFlight flight2 = SpecificFlight();
    flight1.specify_airplane(airplane1);
    flight2.specify_airplane(airplane2);

    // create a flight log
    flight1.create_flight_log();

    // change a plane
    flight1.change_airplane(airplane1, airplane2);

    // make a booking
    PassengerRole passenger1 = PassengerRole("Jack");
    PassengerRole passenger2 = PassengerRole("Rose");
    passenger1.make_booking(flight1);
    passenger2.make_booking(flight2);
    
    // create EmployeeRoles
    EmployeeRole employee1 = EmployeeRole("James", 1);
    EmployeeRole employee2 = EmployeeRole("Mike", 2);
    EmployeeRole employee3 = EmployeeRole("John", 3);
    
    // add crew members
    flight1.add_crew_member(employee1);
    flight1.add_crew_member(employee2);
    flight2.add_crew_member(employee3);

    // find a crew member
    EmployeeRole found_crew_member1 = flight1.find_crew_member("James");
    cout << found_crew_member1.get_name() << endl;

    EmployeeRole found_crew_member2 = flight2.find_crew_member("John");
    cout << found_crew_member2.get_name() << endl;

    // create bookings
    Booking booking1 = Booking(passenger1, flight1);
    Booking booking2 = Booking(passenger2, flight2);

    return 0;
}