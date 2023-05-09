// showingoffilm.h
# pragma once
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Film;

class ShowingOfFilm
{
    public:
        ShowingOfFilm();
        ShowingOfFilm(Film& film, string theatre, string date, string time);
        void set_theatre(string theatre);
        void set_date(string date);
        void set_time(string time);
        void set_film(Film& film);
        string get_showing_info();

        // void link_to_film(Film* film);


    private:
        Film* film;
        string theatre;
        string date;
        string time;
        
};