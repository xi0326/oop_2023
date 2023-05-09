// genre.cpp
# pragma once
# include "genre.h"
# include "film.h"

Genre::Genre(string name): name(name) {}

Genre::Genre(Film& film, string name)
{
    this->set_name(name);
    this->add_film(film);
}

void Genre::set_name(string name)
{
    this->name = name;
}

string Genre::get_name()
{
    return this->name;
}

void Genre::add_film(Film& film)
{
    this->films.push_back(&film);
    film.link_to_genre(this);
}

void Genre::print_all_films_name()
{
    cout << "All films of genre: " << this->name << endl;
    for (auto film: this->films)
    {
        cout << film->get_name() << endl;
    }
}

void Genre::link_to_film(Film* film)
{
    this->films.push_back(film);
}