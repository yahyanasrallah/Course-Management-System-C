/*
=========================================
Learning Management System
Courses Header File
=========================================
*/

#ifndef COURSES_H
#define COURSES_H

/*
====================================
Course Structure

Stores course information
====================================
*/
typedef struct {

    int id;

    char title[100];

    char description[255];

    char category[50];

    int teacherId;

} Course;

/*
====================================
Check Enrollment

Checks if student is already
enrolled in a course
====================================
*/
int enrollmentExists(int courseId);

/*
====================================
Course Functions
====================================
*/
void addCourse();
void viewMyCourses();
void viewAllCourses();
void enrollInCourse();
void viewStudentCourses();
void viewEnrolledStudents();
void editCourse();
void deleteCourse();
void searchCourses();

/*
====================================
Lesson Functions
====================================
*/
void addLesson();
void editLesson();
void viewLessonContent();

/*
====================================
Progress Functions
====================================
*/
void trackProgress();

/*
====================================
Review Functions
====================================
*/
void addReview();
void viewReviews();

#endif