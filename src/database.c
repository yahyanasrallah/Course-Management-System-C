/*
=========================================
Learning Management System
Database Initialization Module

This file handles:
- Database connection
- Creating all required tables
=========================================
*/

/* =================================
            LIBRARIES
================================= */

#include <stdio.h>

#include "../include/database.h"


/*
====================================
Initialize Database

Creates database tables if they
do not already exist
====================================
*/
void initializeDatabase() {

    sqlite3 *db;

    /* Open database connection */
    int result =
        sqlite3_open("database/courses.db", &db);

    if(result == SQLITE_OK) {

        printf(
            "Database connected successfully!\n"
        );

    } else {

        printf(
            "Error: %s\n",
            sqlite3_errmsg(db)
        );

        return;
    }

    /* Users table */
    char *sqlUsers =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "password TEXT NOT NULL,"
        "role TEXT NOT NULL);";

    /* Courses table */
    char *sqlCourses =
        "CREATE TABLE IF NOT EXISTS courses ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT NOT NULL,"
        "description TEXT,"
        "category TEXT,"
        "teacher_username TEXT);";

    /* Enrollments table */
    char *sqlEnrollments =
        "CREATE TABLE IF NOT EXISTS enrollments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_username TEXT,"
        "course_id INTEGER,"
        "progress INTEGER);";

    /* Reviews table */
    char *sqlReviews =
        "CREATE TABLE IF NOT EXISTS reviews ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_username TEXT,"
        "course_id INTEGER,"
        "rating INTEGER,"
        "comment TEXT);";

    /* Lessons table */
    char *sqlLessons =
        "CREATE TABLE IF NOT EXISTS lessons ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "course_id INTEGER,"
        "title TEXT NOT NULL,"
        "content TEXT,"
        "status TEXT);";

    /* Lesson progress table */
    char *sqlLessonProgress =
        "CREATE TABLE IF NOT EXISTS lesson_progress ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_username TEXT,"
        "lesson_id INTEGER,"
        "completed INTEGER);";

    /* Execute SQL queries */
    sqlite3_exec(db, sqlUsers, 0, 0, 0);
    sqlite3_exec(db, sqlCourses, 0, 0, 0);
    sqlite3_exec(db, sqlEnrollments, 0, 0, 0);
    sqlite3_exec(db, sqlReviews, 0, 0, 0);
    sqlite3_exec(db, sqlLessons, 0, 0, 0);
    sqlite3_exec(db, sqlLessonProgress, 0, 0, 0);

    printf("Tables created successfully!\n");

    /* Close database connection */
    sqlite3_close(db);
}