// film.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Genre;
class ShowingOfFilm;
class ReelOfFilm;

class Film
{
    public:
        Film();
        Film(string name, ReelOfFilm& reel_of_film, Genre& genre);
        void set_name(string name);
        string get_name();
        void add_genre(Genre& genre);
        void add_showing(ShowingOfFilm& showing_of_film);
        void set_reel(ReelOfFilm& reel_of_film);
        void print_all_genre();
        void print_all_showing_info();

        void link_to_reel(ReelOfFilm* reel_of_film);
        void link_to_genre(Genre* genre);
        // void link_to_showing(ShowingOfFilm& showing_of_film);

    private:
        string name;
        ReelOfFilm* reel_of_film;
        vector<Genre*> genres;
        vector<ShowingOfFilm*> showings;

};