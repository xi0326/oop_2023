// genre.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Film;

class Genre
{
    public:
        Genre(string name);
        Genre(Film& film, string name);
        void set_name(string name);
        string get_name();
        void add_film(Film& film);
        void print_all_films_name();

        void link_to_film(Film* film);

    private:
        string name;
        vector<Film*> films;

};