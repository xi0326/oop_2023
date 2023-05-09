// reeloffilm.h
# pragma once
# include <string>

using namespace std;

// forward declaration
class Film;

class ReelOfFilm
{
    public:
        ReelOfFilm();
        ReelOfFilm(int serial_number);
        // ReelOfFilm(int serial_number, Film& film);
        void set_serial_number(int serial_number);
        int get_serial_number();
        void set_film(Film& film);

        void link_to_film(Film* film);


    private:
        int serial_number;
        Film* film;
};

