// main.cpp
# pragma once
# include "genre.h"
# include "film.h"
# include "reeloffilm.h"
# include "showingoffilm.h"

int main()
{
    // create new genre
    Genre science_fiction = Genre("Science");
    Genre comedy = Genre("Comedy");

    // create new reel
    ReelOfFilm star_wars_weel = ReelOfFilm(1000);
    ReelOfFilm breaking_bad_weel = ReelOfFilm(1001);

    // create new film
    Film star_wars = Film("Star Wars", star_wars_weel, science_fiction);
    Film breaking_bad = Film("Breaking Bad", breaking_bad_weel, comedy);

    // create new showing
    ShowingOfFilm showing1 = ShowingOfFilm(star_wars, "Phoenix Cinema", "20230413", "19:00");
    ShowingOfFilm showing2 = ShowingOfFilm(star_wars, "Phoenix Cinema", "20230413", "21:00");
    ShowingOfFilm showing3 = ShowingOfFilm(breaking_bad, "Chicken Cinema", "20230414", "07:00");
    ShowingOfFilm showing4 = ShowingOfFilm(breaking_bad, "Phoenix Cinema", "20230415", "14:00");
    ShowingOfFilm showing5 = ShowingOfFilm(star_wars, "Chicken Cinema", "20230414", "21:00");

    // check showing info
    star_wars.print_all_showing_info();
    breaking_bad.print_all_showing_info();

    // check all science fictions
    science_fiction.print_all_films_name();
    comedy.print_all_films_name();

    return 0;
}