// administrativeassistant.cpp
# pragma once
# include "administrativeassistant.h"
# include "manager.h"


AdministrativeAssistant::AdministrativeAssistant(): name(""){}

AdministrativeAssistant::AdministrativeAssistant(string name, Manager& manager)
{
    this->name = name;
    this->managers.push_back(&manager);

    // link to manager
    manager.link_to_administrative_assistant(*this);
}

void AdministrativeAssistant::set_name(string name)
{
    this->name = name;
}

string AdministrativeAssistant::get_name()
{
    return this->name;
}

void AdministrativeAssistant::print_all_managers_name()
{
    for (auto manager: this->managers)
    {
        cout << manager->get_name() << endl;
    }   
}

void AdministrativeAssistant::add_new_manager(Manager& manager)
{
    this->managers.push_back(&manager);

    // link to manager
    manager.link_to_administrative_assistant(*this);
}

void AdministrativeAssistant::link_to_manager(Manager& manager)
{
    this->managers.push_back(&manager);
}