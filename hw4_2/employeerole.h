// employeerole.h
# pragma once
# include "personrole.h"

using namespace std;

class EmployeeRole: public PersonRole
{
    public:
        EmployeeRole(); // this constructor is not used
        EmployeeRole(int employee_id);  // this constructor is for the supervisors
        EmployeeRole(int employee_id, EmployeeRole& supervisor);
        int get_employee_id();
        void set_supervisor(EmployeeRole& supervisor);
        // @ override
        void delete_role();

    private:
        int employee_id;
        vector<SpecificFlight*> filght_list;
        EmployeeRole* supervisor;
        vector<EmployeeRole*> subordinates;
};