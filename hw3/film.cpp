// film.cpp
# pragma once
# include "film.h"
# include "genre.h"
# include "showingoffilm.h"
# include "reeloffilm.h"

Film::Film(): name(""), reel_of_film(nullptr) {}

Film::Film(string name, ReelOfFilm& reel_of_film, Genre& genre)
{
    this->set_name(name);
    this->set_reel(reel_of_film);
    this->add_genre(genre);
}

void Film::set_name(string name)
{
    this->name = name;
}

string Film::get_name()
{
    return this->name;
}

void Film::add_genre(Genre& genre)
{
    this->genres.push_back(&genre);
    genre.link_to_film(this);
}

void Film::add_showing(ShowingOfFilm& showing_of_film)
{
    this->showings.push_back(&showing_of_film);
}

void Film::set_reel(ReelOfFilm& reel_of_film)
{
    this->reel_of_film = &reel_of_film;
    reel_of_film.link_to_film(this);
}

void Film::print_all_genre()
{
    cout << "All genres of the movie " << this->name << endl;
    for (auto genre: this->genres)
    {
        cout << genre->get_name() << endl;
    }
}

void Film::print_all_showing_info()
{
    cout << "All showing infos of the movie " << this->name << endl;
    for (auto showing: this->showings)
    {
        cout << showing->get_showing_info() << endl;
    }
}

void Film::link_to_reel(ReelOfFilm* reel_of_film)
{
    this->reel_of_film = reel_of_film;
}

void Film::link_to_genre(Genre* genre)
{
    this->genres.push_back(genre);
}
