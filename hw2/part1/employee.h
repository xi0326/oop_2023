// employee.h
# pragma once
# include <string>
# include <iostream>

using namespace std;

// forward declaration
class Company;
class Office;

class Employee
{
    public:
        Employee();
        Employee(string name, Company& company, Office& office);

        void set_name(string name);
        void join_company(Company& Company);
        void set_office(Office& office);
        string get_name();
        Company get_company();
        Office get_office();

    private:
        string name;
        Company* company;
        Office* office;
};