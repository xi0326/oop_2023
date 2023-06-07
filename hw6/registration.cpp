// registration.cpp -- Registration class implementation

# include "registration.h"
# include "student.h"
# include "coursesection.h"

Registration::Registration()
{
    this->student = nullptr;
    this->course_section = nullptr;
}

Registration::Registration(Student& student, CourseSection& course_section)
{
    this->student = &student;
    this->course_section = &course_section;
    student.add_to_schedule(this);
    course_section.add_link_to_registration(this);
}

string Registration::get_course_name()
{
    return this->course_section->get_course_name();
}

void Registration::unregister_student() //  ~Registration()
{
    this->student->remove_registration(this);
    delete this;
}
