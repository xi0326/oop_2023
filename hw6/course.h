// course.h -- Course class interface

# pragma once
# include <iostream>
# include <string>
# include <vector>
# include <semaphore>
# include <thread>

using namespace std;

// forward declaration
class CourseSection;

class Course
{
    public:
        Course();
        Course(string name, int minimum, int maximum);
        Course(string name, int minimum, int maximum, Course& prerequisite);
        string get_name();
        void add_prerequisite(Course& course);
        Course* get_prerequisite();
        int get_minimum();
        int get_maximum();
        void add_link_to_section(CourseSection* section);   // link to a course section

    private:
        string name;
        int minimum;
        int maximum;
        Course* prerequisite;
        vector<CourseSection*> sections;
        
};