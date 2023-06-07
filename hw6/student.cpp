// student.cpp -- Student class implementation

# include "student.h"
# include "course.h"
# include "registration.h"

Student::Student()
{
    this->name = "";
    this->id = 0;
}

Student::Student(string name, int id)
{
    this->name = name;
    this->id = id;
}

Student::Student(string name, int id, vector<Course*> passed_courses)
{
    this->name = name;
    this->id = id;
    this->passed_courses = passed_courses;
}

string Student::get_name()
{
    return this->name;
}

// check if the student has passed the course
void Student::has_prerequisite(Course* prerequisite_course, Course* special_permission_course, bool& student_has_passed_prerequisite)
{
    // if there is no prerequisite, then the student has passed the prerequisite
    if (prerequisite_course == nullptr)
    {
        student_has_passed_prerequisite = true;
        return;
    }

    // cout << "Checking if " << this->name << " has passed " << course->get_name() << "..." << endl;
    for (int i = 0; i < this->passed_courses.size(); i++)
    {
        if (this->passed_courses[i] == prerequisite_course)
        {
            student_has_passed_prerequisite = true;
            return;
        }
    }

    // if the student has special permission for the course, then he/she has passed the prerequisite
    if (this->has_special_permission(special_permission_course))
        student_has_passed_prerequisite = true;
    else
        student_has_passed_prerequisite = false;
    
    return;
}

void Student::add_to_schedule(Registration* registration)
{
    this->registrations.push_back(registration);
}

void Student::remove_registration(Registration* registration)
{
    for (int i = 0; i < this->registrations.size(); i++)
        if (this->registrations[i] == registration)
        {
            this->registrations.erase(this->registrations.begin() + i);
            return;
        }
}

void Student::set_special_permission_course(Course* course)
{
    this->special_permission_courses.push_back(course);
}

bool Student::has_special_permission(Course* course)
{
    for (int i = 0; i < this->special_permission_courses.size(); i++)
        if (this->special_permission_courses[i] == course)
            return true;
    
    return false;
}

void Student::print_schedule()
{
    cout << "Student " << this->name << " has the following schedule:" << endl;
    for (auto registration : this->registrations)
        cout << registration->get_course_name() << endl;
    cout << endl;
}