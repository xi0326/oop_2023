// main.cpp -- for testing the classes

# include "course.h"
# include "student.h"
# include "registration.h"
# include "coursesection.h"

using namespace std;

int main()
{
    // create courses
    Course DS("Data Structure", 2, 3);
    Course OS("Operating System", 2, 3);
    Course OOP("Object Oriented Programming", 2, 3, OS);

    // create students
    Student student1("Alice", 1, {&OS});
    Student student2("Bob", 2);
    Student student3("Jimmy", 3);
    student3.set_special_permission_course(&OOP);

    Student student4("John", 4, {&DS, &OS});
    Student student5("Jane", 5, {&OS});

    // create course sections
    CourseSection DS_section(DS);
    CourseSection OS_section(OS);
    CourseSection OOP_section(OOP);

    // registeration
    cout << "Registeration DS & OS" << endl;
    DS_section.open_registration();    // turn the course to open state
    DS_section.request_to_register(student1);  // should NOT be rejected, since DS has no prerequisite
    DS_section.request_to_register(student2);  // should NOT be rejected, since DS has no prerequisite

    OS_section.request_to_register(student2);  // should be rejected, since OS is not in Open State

    cout << "==============================" << endl;
    cout << "Registeration OOP" << endl;
    OOP_section.open_registration();    // turn the course to open state

    // simulate 5 students requesting to register OOP
    /* student1 should NOT be rejected, because student1 has passed OS
       student2 should be rejected, because student2 has not passed OS
       student3 should NOT be rejected, because student3 has special permission
       student4 should NOT be rejected, because student4 has passed OS
       student5 should NOT be rejected, because student1 has passed OS
       A stuent will be reject since course OOP is full */
    thread OOP_threads[5];
    Student OOP_students[5] = {student1, student2, student3, student4, student5};

    for (int i = 0; i < 5; i++)
        OOP_threads[i] = thread(&CourseSection::request_to_register, &OOP_section, ref(OOP_students[i]));

    for (int i = 0; i < 5; i++)
        OOP_threads[i].join();

    

    return 0;
}