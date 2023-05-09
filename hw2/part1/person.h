// person.h
# pragma once
# include <string>
# include <vector>
# include <iostream>

using namespace std;

// forward declaration
class BoardOfDirector;

class Person
{
    public:
        Person();
        Person(string name);

        void set_name(string name);
        string get_name();
        void add_new_board_of_directors(BoardOfDirector& new_board_of_director);
        void print_all_board_of_directors_name();

    private:
        string name;
        vector<BoardOfDirector*> board_of_directors;

};