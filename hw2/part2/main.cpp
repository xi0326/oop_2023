// main.cpp
# pragma once
# include"administrativeassistant.h"
# include "manager.h"

using namespace std;

int main()
{
    // create 3 managers
    Manager manager1 = Manager();
    Manager manager2 = Manager();
    Manager manager3 = Manager();

    manager1.set_name("Steven");
    manager2.set_name("Alice");
    manager3.set_name("Bob");

    // create 5 administrative_assistants
    AdministrativeAssistant administrative_assistant1 = 
    AdministrativeAssistant("Cindy", manager1);
    AdministrativeAssistant administrative_assistant2 = AdministrativeAssistant("Cathie", manager1);
    AdministrativeAssistant administrative_assistant3 = AdministrativeAssistant("Eric", manager2);
    AdministrativeAssistant administrative_assistant4 = AdministrativeAssistant("Jeff", manager2);
    AdministrativeAssistant administrative_assistant5 = AdministrativeAssistant("Kyrie", manager3);

    // assign managers to administrative_assistants
    administrative_assistant1.add_new_manager(manager2);
    administrative_assistant2.add_new_manager(manager3);
    administrative_assistant3.add_new_manager(manager1);


    // test
    manager1.print_all_administrative_assistants_name();
    manager2.print_all_administrative_assistants_name();
    manager3.print_all_administrative_assistants_name();


    return 0;
}