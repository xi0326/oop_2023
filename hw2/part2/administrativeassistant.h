// administrativeassistant.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// foward declaration
class Manager;

class AdministrativeAssistant
{
    public:
        AdministrativeAssistant();
        AdministrativeAssistant(string name, Manager& manager);
        void set_name(string name);
        string get_name();
        void print_all_managers_name();
        void add_new_manager(Manager& new_manager);
        void link_to_manager(Manager& new_manager);

    
    private:
        string name;
        vector<Manager*> managers;

};