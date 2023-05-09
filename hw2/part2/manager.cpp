// manager.cpp
# pragma once
# include "manager.h"
# include "administrativeassistant.h"

Manager::Manager(): name(""){}

Manager::Manager(string name, AdministrativeAssistant& administrative_assistant)
{
    this->name = name;
    this->administrative_assistants.push_back(&administrative_assistant);

    // link to administrative_assistant
    administrative_assistant.link_to_manager(*this);
}

void Manager::set_name(string name)
{
    this->name = name;
}

string Manager::get_name()
{
    return this->name;
}

void Manager::print_all_administrative_assistants_name()
{
    for (auto administrative_assistant: this->administrative_assistants)
    {
        cout << administrative_assistant->get_name() << endl;
    }
}

void Manager::add_new_administrative_assistant(AdministrativeAssistant& administrative_assistant)
{
    this->administrative_assistants.push_back(&administrative_assistant);

    // link to administrative_assistant
    administrative_assistant.link_to_manager(*this);
}

void Manager::link_to_administrative_assistant(AdministrativeAssistant& administrative_assistant)
{
    this->administrative_assistants.push_back(&administrative_assistant);
}