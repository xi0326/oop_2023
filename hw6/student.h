// student.h -- Student class interface

# pragma once
# include <iostream>
# include <string>
# include <vector>

using namespace std;

// forward declaration
class Course;
class Registration;

class Student
{
    public:
        Student();
        Student(string name, int id);
        Student(string name, int id, vector<Course*> passed_courses);   // student with passed courses
        string get_name();
        void has_prerequisite(Course* prerequisite_course, Course* special_permission_course, bool& student_has_passed_prerequisite); // check if the student has passed the course
        void add_to_schedule(Registration* registration);   // void add_link_to_registration(Registration* registration);
        void remove_registration(Registration* registration);
        void set_special_permission_course(Course* course);
        void print_schedule();

    private:
        string name;
        int id;
        vector<Course*> passed_courses;
        vector<Registration*> registrations;
        vector<Course*> special_permission_courses;
        bool has_special_permission(Course* course);
};