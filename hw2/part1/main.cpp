// main.cpp
# pragma once
# include "company.h"
# include "employee.h"
# include "office.h"
# include "boardofdirector.h"
# include "person.h"
# include <iostream>

using namespace std;

int main()
{

    // create a few people
    Person person1 = Person("Jack");
    Person person2 = Person("Alice");
    Person person3 = Person("Bob");

    // create a new board_of_director
    BoardOfDirector board_of_director = BoardOfDirector();
    board_of_director.set_name("board_of_director_of_ISMP");

    cout << board_of_director.get_name() << endl;

    // add people to board_of_director
    board_of_director.add_new_person(person1);
    board_of_director.add_new_person(person2);
    board_of_director.add_new_person(person3);

    person1.print_all_board_of_directors_name();

    // create a new company
    Company company = Company("ISMP", board_of_director);

    // create two new office
    Office office1 = Office("Taipei");
    Office office2 = Office("Tainan");

    // create few employees
    Employee employee1 = Employee("Cindy", company, office1);
    Employee employee2 = Employee("John", company, office1);
    Employee employee3 = Employee("Misaki", company, office1);
    Employee employee4 = Employee("Stanley", company, office2);
    Employee employee5 = Employee("Steven", company, office2);

    // test
    cout << "board_of_director info" << endl;
    cout << board_of_director.get_company().get_name() << endl;
    board_of_director.print_people_name();

    cout << "company info" << endl;
    cout << company.get_board_of_director().get_name() << endl;
    company.print_all_employees_name();

    cout << "office 1 info (Taipei)" << endl;
    office1.print_all_employees_name();

    cout << "office 2 info (Tainan)" << endl;
    office2.print_all_employees_name();

    return 0;
}