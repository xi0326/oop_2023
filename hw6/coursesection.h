// coursesection.h -- CourseSection class interface

# pragma once
# include <iostream>
# include <string>
# include <vector>
# include <thread>
# include <semaphore>

// for coloured output
# define RESET   "\033[0m"
# define RED     "\033[31m"      /* Red */
# define GREEN   "\033[32m"      /* Green */

using namespace std;

// forward declaration
class Course;
class Registration;
class Student;

class CourseSection
{
    public:
        CourseSection();
        CourseSection(Course& course);
        string get_course_name();
        void open_registration();
        void close_registration();
        void cancel_registration();
        void request_to_register(Student& student);
        void is_full(bool& course_is_full, counting_semaphore<1>& sem);
        void add_link_to_registration(Registration* registration);
    
    private:
        Course* course;
        vector<Registration*> registrations;
        bool open = false;
        bool closed_or_canceled = false;
        counting_semaphore<1> sem{1};
        void unregister_students();

};