/*
=========================================
Learning Management System
User Header File

This file contains:
- User structure
- User roles
- Function prototypes
=========================================
*/

#ifndef USERS_H
#define USERS_H

/* =================================
            USER ROLES
================================= */

#define STUDENT_ROLE "STUDENT"

#define TEACHER_ROLE "TEACHER"

/*
====================================
User Structure

Stores user information
====================================
*/
typedef struct {

    int id;

    char username[50];

    char password[50];

    char role[20];

} User;

/* =================================
        FUNCTION PROTOTYPES
================================= */

void registerUser();
void saveUser(User user);
int userExists(char username[]);
void showStudentMenu();
void showTeacherMenu();
void loginUser();

#endif