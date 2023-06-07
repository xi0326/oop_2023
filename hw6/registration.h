// registration.h -- Registration class interface

# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Student;
class CourseSection;

class Registration
{
    public:
        Registration();
        Registration(Student& student, CourseSection& course_section);
        string get_course_name();
        void unregister_student();  //  ~Registration() and remove the link
    
    private:
        Student* student;
        CourseSection* course_section;
};