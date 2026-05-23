/*
=========================================
Learning Management System
Enrollment Header File

This file contains:
- Enrollment structure
=========================================
*/

#ifndef ENROLLMENT_H
#define ENROLLMENT_H

/*
====================================
Enrollment Structure

Stores student enrollment data
====================================
*/
typedef struct {

    int id;

    int studentId;

    int courseId;

    int progress;

} Enrollment;

#endif