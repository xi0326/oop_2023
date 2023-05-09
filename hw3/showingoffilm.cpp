// showingoffilm.cpp
# pragma once
# include "showingoffilm.h"
# include "film.h"

ShowingOfFilm::ShowingOfFilm(): film(nullptr), theatre(""), date(""), time("") {}

ShowingOfFilm::ShowingOfFilm(Film& film, string theatre, string date, string time)
{
    this->set_film(film);
    this->set_theatre(theatre);
    this->set_date(date);
    this->set_time(time);
}

void ShowingOfFilm::set_theatre(string theatre)
{
    this->theatre = theatre;
}

void ShowingOfFilm::set_date(string date)
{
    this->date = date;
}

void ShowingOfFilm::set_time(string time)
{
    this->time = time;
}

void ShowingOfFilm::set_film(Film& film)
{
    this->film = &film;
    film.add_showing(*this);
}

string ShowingOfFilm::get_showing_info()
{
    return "Showing of " + this->film->get_name() + " is in the " + this->theatre + " at " + this->date + " " + this->time;
}