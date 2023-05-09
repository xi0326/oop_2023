// reeloffilm.cpp
# pragma once
# include "reeloffilm.h"
# include "film.h"

ReelOfFilm::ReelOfFilm(): serial_number(0), film(nullptr) {}

// ReelOfFilm::ReelOfFilm(int serial_number, Film& film)
ReelOfFilm::ReelOfFilm(int serial_number)
{
    this->set_serial_number(serial_number);
    // this->set_film(film);
}

void ReelOfFilm::set_serial_number(int serial_number)
{
    this->serial_number = serial_number;
}

int ReelOfFilm::get_serial_number()
{
    return this->serial_number;
}

void ReelOfFilm::set_film(Film& film)
{
    this->film = &film;
    film.link_to_reel(this);
}

void ReelOfFilm::link_to_film(Film* film)
{
    this->film = film;
}