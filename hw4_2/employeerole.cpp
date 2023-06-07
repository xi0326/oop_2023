// employeerole.cpp
# pragma once
# include "employeerole.h"
# include "specificflight.h"


EmployeeRole::EmployeeRole() {}

EmployeeRole::EmployeeRole(int employee_id)
{
    this->employee_id = employee_id;
}

EmployeeRole::EmployeeRole(int employee_id, EmployeeRole& supervisor)
{
    this->employee_id = employee_id;
    this->set_supervisor(supervisor);
}

int EmployeeRole::get_employee_id()
{
    return this->employee_id;
}

void EmployeeRole::set_supervisor(EmployeeRole& supervisor)
{
    this->supervisor = &supervisor;
    supervisor.subordinates.push_back(this);
}

// @ override
void EmployeeRole::delete_role()
{
    // delete the supervisor's record of the subordinates
    for (auto subordinate: this->subordinates)
    {
        subordinate->supervisor = nullptr;
    }

    // delete the employee's record from flights crew list
    for (auto flight: this->filght_list)
    {
        flight->delete_crew_member(*this);
    }

    delete this;
}