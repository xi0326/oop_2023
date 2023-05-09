// flightlog.cpp
# pragma once
# include "flightlog.h"
# include "specificflight.h"


FlightLog::FlightLog() {}

FlightLog::FlightLog(SpecificFlight &flight)
{
    this->flight = &flight;
}

void FlightLog::write_log(string data)
{
    this->log_data = data;
}

string FlightLog::get_log()
{
    return this->log_data;
}