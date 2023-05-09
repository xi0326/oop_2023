// manager.h
# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// foward declaration
class AdministrativeAssistant;

class Manager
{
    public:
        Manager();
        Manager(string name, AdministrativeAssistant& administrative_assistant);
        void set_name(string name);
        string get_name();
        void print_all_administrative_assistants_name();
        void add_new_administrative_assistant(AdministrativeAssistant& administrative_assistant);
        void link_to_administrative_assistant(AdministrativeAssistant& administrative_assistant);

    private:
        string name;
        vector<AdministrativeAssistant*> administrative_assistants;
};