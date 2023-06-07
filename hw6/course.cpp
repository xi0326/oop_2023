// course.cpp -- Course class implementation

# include "course.h"

Course::Course()
{
    this->name = "";
    this->minimum = 0;
    this->maximum = 0;
    this->prerequisite = nullptr;
}

Course::Course(string name, int minimum, int maximum)
{
    this->name = name;
    this->minimum = minimum;
    this->maximum = maximum;
    this->prerequisite = nullptr;
}

Course::Course(string name, int minimum, int maximum, Course& prerequisite)
{
    this->name = name;
    this->minimum = minimum;
    this->maximum = maximum;
    this->prerequisite = &prerequisite;
}

string Course::get_name()
{
    return this->name;
}

void Course::add_prerequisite(Course& course)
{
    this->prerequisite = &course;
}

Course* Course::get_prerequisite()
{
    return this->prerequisite;
}

int Course::get_minimum()
{
    return this->minimum;
}

int Course::get_maximum()
{
    return this->maximum;
}

void Course::add_link_to_section(CourseSection* section)
{
    this->sections.push_back(section);
}