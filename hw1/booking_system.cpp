// booking_system.cpp
# pragma once
#include "booking_system.h"
#include <iostream>

// booking the seat with basic info
void BookingSystem::booking()
{

    int input;
    string name;
    string phone_number;
    string sex;


    // infinite loop
    while (true)
    {
        cout << "Which bus you want to order?" << endl << "press 1 for morning, 2 for afternoon, 3 for both, 0 for quit" << endl;
        cin >> input;
        
        // quit the while loop
        if (input == 0)
            break;

        // get the name
        cout << "Please input your name" << endl;
        cin >> name;

        // get the phone number
        cout << "Please input your phone number" << endl;
        cin >> phone_number;

        //get the sex
        cout << "Please input your sex" << endl;
        cin >> sex;

        // initialise the passenger with basic info
        Person new_passenger = Person(name, phone_number, sex);

        // add the passenger to morning bus
        if (input == 1)
        {
            this->bus_morning.add_passenger(new_passenger);
        }
        // add the passenger to afternoon bus
        else if (input == 2)
        {
            this->bus_afternoon.add_passenger(new_passenger);
        }
        // add the passenger to the both
        else if (input == 3)
        {
            this->bus_morning.add_passenger(new_passenger);
            this->bus_afternoon.add_passenger(new_passenger);
        }
    }

}

// print out all booking details
void BookingSystem::print_booking_details()
{
    cout << "Here are the booking details:" << endl;
    this->bus_morning.print_all_passengers();
    this->bus_afternoon.print_all_passengers();
}

// inquiry system interface
void BookingSystem::inquiry()
{
    string name;

    // infinite loop
    while (true)
    {
        cout << "Please input the name who you want to search, " << endl << "press q for quit" << endl;
        cin >> name;

        if (name == "quit" || name == "q")
        {
            break;
        }
        else
        {
            // if the passenger booked the morning ticket
            if (this->bus_morning.is_passenger(name))
            {
                cout << name + " booked the morning ticket." << endl;
            }
            
            // if the passenger booked the afternoon ticket
            if (this->bus_afternoon.is_passenger(name))
            {
                cout << name + " booked the afternoon ticket." << endl;
            }

            // if the passenger did not book any ticket
            if (!this->bus_morning.is_passenger(name) && !this->bus_afternoon.is_passenger(name))
                cout << name + " did not book any ticket." << endl;   
        }
    }
}

// for testing
void BookingSystem::system_test()
{
    // run the booking system
    this->booking();

    // get the details
    this->print_booking_details();

    // run inquiry system
    this->inquiry();
}