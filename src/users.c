/*
=========================================
Learning Management System
User Management Module

This file handles:
- User registration
- User login
- Role management
- Student menu
- Teacher menu
=========================================
*/

/* =================================
            LIBRARIES
================================= */

#include <stdio.h>
#include <string.h>
#include "../include/sqlite3.h"
#include "../include/users.h"
#include "../include/courses.h"

/* =================================
        GLOBAL VARIABLES
================================= */

static int foundUser = 0;
static char loggedRole[20];

char currentUsername[50];


/*
====================================
User Authentication Callback

Checks if user exists and stores:
- logged role
- current username
====================================
*/
static int checkUserCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    foundUser = 1;

    strcpy(loggedRole, argv[3]);
    strcpy(currentUsername, argv[1]);

    return 0;
}

/*
====================================
Save User

Stores new user information
inside the database
====================================
*/
void saveUser(User user) {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[500];

    sprintf(
        sql,
        "INSERT INTO users (username, password, role) "
        "VALUES ('%s', '%s', '%s');",
        user.username,
        user.password,
        user.role
    );

    sqlite3_exec(db, sql, 0, 0, 0);

    printf(
        "\n\033[1;32mUser saved successfully!\033[0m\n"
    );

    sqlite3_close(db);
}

/*
====================================
Register User

Allows student or teacher
to create a new account
====================================
*/
void registerUser() {

    printf("\n===== REGISTER =====\n");

    int roleChoice;

    User newUser;

    printf("Select role:\n");

    printf("1. Student\n");
    printf("2. Teacher\n");
    printf("3. Exit\n");

    printf("\nChoose role: ");
    scanf("%d", &roleChoice);

    if(roleChoice == 3) {

        return;
    }

    printf("Enter username: ");
    scanf("%s", newUser.username);

    printf("Enter password: ");
    scanf("%s", newUser.password);

    printf("\nRegistration Data:\n");

    switch(roleChoice) {

        case 1:
            strcpy(newUser.role, STUDENT_ROLE);
            break;

        case 2:
            strcpy(newUser.role, TEACHER_ROLE);
            break;

        default:
            printf(
                "\n\033[1;31mInvalid role.\033[0m\n"
            );
            return;
    }

    printf("Username: %s\n", newUser.username);

    printf("Password: %s\n", newUser.password);

    printf("Role: %s\n", newUser.role);

    if(userExists(newUser.username)) {

        printf(
            "\n\033[1;31mUsername already exists!\033[0m\n"
        );

    } else {

        saveUser(newUser);
    }
}

/*
====================================
Check Existing User

Checks if username already exists
in the database
====================================
*/
int userExists(char username[]) {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    foundUser = 0;

    char sql[500];

    sprintf(
        sql,
        "SELECT * FROM users "
        "WHERE username='%s';",
        username
    );

    sqlite3_exec(db, sql, checkUserCallback, 0, 0);

    sqlite3_close(db);

    return foundUser;
}

/*
====================================
Student Menu

Displays all student features
====================================
*/
void showStudentMenu() {

    int choice;

    while(1) {

        printf("\n===== STUDENT MENU =====\n");

        printf("1. View Courses\n");
        printf("2. Search Course\n");
        printf("3. Enroll in Course\n");
        printf("4. My Courses\n");
        printf("5. View Lesson Content\n");
        printf("6. Add Review\n");
        printf("7. Track Progress\n");
        printf("8. Logout\n");

        printf("\nChoose an option: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                viewAllCourses();
                break;

            case 2:
                searchCourses();
                break;

            case 3:
                enrollInCourse();
                break;

            case 4:
                viewStudentCourses();
                break;

            case 5:
                viewLessonContent();
                break;

            case 6:
                addReview();
                break;

            case 7:
                trackProgress();
                break;

            case 8:
                printf("\nLogging out...\n");
                return;

            default:
                printf(
                    "\n\033[1;31mInvalid option.\033[0m\n"
                );
        }
    }
}

/*
====================================
Teacher Menu

Displays all teacher features
====================================
*/
void showTeacherMenu() {

    int choice;

    while(1) {

        printf("\n===== TEACHER MENU =====\n");

        printf("1. Add Course\n");
        printf("2. Edit Course\n");
        printf("3. Delete Course\n");
        printf("4. View My Courses\n");
        printf("5. View Enrolled Students\n");
        printf("6. Add Lesson\n");
        printf("7. Edit Lesson\n");
        printf("8. View Reviews\n");
        printf("9. Logout\n");

        printf("\nChoose an option: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addCourse();
                break;

            case 2:
                editCourse();
                break;

            case 3:
                deleteCourse();
                break;

            case 4:
                viewMyCourses();
                break;

            case 5:
                viewEnrolledStudents();
                break;

            case 6:
                addLesson();
                break;

            case 7:
                editLesson();
                break;

            case 8:
                viewReviews();
                break;

            case 9:
                printf("\nLogging out...\n");
                return;

            default:
                printf(
                    "\n\033[1;31mInvalid option.\033[0m\n"
                );
        }
    }
}

/*
====================================
User Login

Authenticates username and password
then opens the correct menu
====================================
*/
void loginUser() {

    char username[50];
    char password[50];

    printf("\n===== LOGIN =====\n");

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    foundUser = 0;

    char sql[500];

    sprintf(
        sql,
        "SELECT * FROM users "
        "WHERE username='%s' "
        "AND password='%s';",
        username,
        password
    );

    sqlite3_exec(db, sql, checkUserCallback, 0, 0);

    sqlite3_close(db);

    if(foundUser) {

        printf(
            "\n\033[1;32mLogin successful!\033[0m\n"
        );

        if(strcmp(loggedRole, STUDENT_ROLE) == 0) {

            showStudentMenu();

        } else if(
            strcmp(loggedRole, TEACHER_ROLE) == 0
        ) {

            showTeacherMenu();
        }

    } else {

        printf(
            "\n\033[1;31mInvalid username or password!\033[0m\n"
        );
    }
}