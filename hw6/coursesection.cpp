// coursesection.cpp -- CourseSection class implementation

# include "coursesection.h"
# include "course.h"
# include "registration.h"
# include "student.h"

CourseSection::CourseSection()
{
    this->course = NULL;
}

CourseSection::CourseSection(Course& course)
{
    this->course = &course;
    course.add_link_to_section(this);
}

string CourseSection::get_course_name()
{
    return this->course->get_name();
}

void CourseSection::open_registration()
{
    if (!this->closed_or_canceled)  // must be in Planned state
        this->open = true;  // to open_not_enough_students state
}

void CourseSection::close_registration()
{
    // to Closed or Canceled state
    this->open = false;
    this->closed_or_canceled = true;

    if (this->registrations.size() < this->course->get_minimum())   // student not enough
        this->unregister_students(); // to Canceled state
}

void CourseSection::cancel_registration()
{
    // to Canceled state
    this->open = false;
    this->closed_or_canceled = true;
    this->unregister_students();
}

// receive a course registration request from a student
void CourseSection::request_to_register(Student& student)
{
    // if the course section is in Open state
    if (this->open)
    {
        Course* prerequisite = this->course->get_prerequisite();
        bool student_has_passed_prerequisite = false;
        bool course_is_full = true;
        
        // check if the student has passed the prerequisite
        thread prerequisite_thread(&Student::has_prerequisite, &student, ref(prerequisite), ref(this->course), ref(student_has_passed_prerequisite));
        thread course_thread(&CourseSection::is_full, this, ref(course_is_full), ref(this->sem));

        prerequisite_thread.join();
        course_thread.join();   // critical section start

        if (student_has_passed_prerequisite && !course_is_full)
        {
            // indirectly calls add_link_to_registration()
            Registration* registration = new Registration(student, *this);
            cout << GREEN << "ACCEPTED: " << RESET;
            cout << "Student " << student.get_name() << " has registered for course " << this->course->get_name() << endl;
        }
        else if (!student_has_passed_prerequisite)
        {
            cout << RED << "REJECTED: " << RESET;
            cout << "Student " << student.get_name() << " has NOT passed the prerequisite for course " << this->course->get_name() << endl;
        }
        else if (course_is_full)
        {
            cout << RED << "REJECTED: " << RESET;
            cout << "Student " << student.get_name() << " cannot register for course " << this->course->get_name() << " since ";
            cout << "Course " << this->course->get_name() << " is full" << endl;
        }

        this->sem.release();    // release the semaphore
        // critical section end

        // Check for automatic transition to Closed state
        if (this->registrations.size() >= this->course->get_maximum())
        {
            // to Closed state
            this->open = false;
            this->closed_or_canceled = true;
        }
    }

    else
    {
        cout << RED << "REJECTED: " << RESET;
        cout << "Registration is not open for course " << this->course->get_name() << endl;
    }
}

void CourseSection::is_full(bool& course_is_full, counting_semaphore<1>& sem)
{
    sem.acquire();

    if (this->registrations.size() >= this->course->get_maximum())
        course_is_full = true;
    else
        course_is_full = false;

    // sem.release();
}

void CourseSection::add_link_to_registration(Registration* registration)
{
    this->registrations.push_back(registration);
}

void CourseSection::unregister_students()
{
    for (auto registration : this->registrations)
        registration->unregister_student();

    // clear the vector
    this->registrations.clear();
}