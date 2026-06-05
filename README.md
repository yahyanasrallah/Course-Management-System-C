# Course Management System (C + SQLite)

A console-based Learning Management System developed in C using SQLite for persistent data storage.

## Features

### Teacher Features

* Add Courses
* Edit Courses
* Delete Courses
* View Personal Courses
* Add Lessons
* Edit Lessons
* View Enrolled Students
* View Student Reviews

### Student Features

* View Available Courses
* Search Courses
* Enroll in Courses
* View Enrolled Courses
* Access Lesson Content
* Mark Lessons as Completed
* Track Learning Progress
* Submit Course Reviews

## Technologies Used

* C Programming Language
* SQLite Database
* Modular Programming
* Structured Programming
* File Organization with Header Files

## Project Structure

```text
C_EX1/
│
├── build/
│   └── app.exe
│
├── database/
│   └── courses.db
│
├── include/
│   ├── users.h
│   ├── courses.h
│   ├── database.h
│   ├── enrollment.h
│   ├── reviews.h
│   └── sqlite3.h
│
├── src/
│   ├── main.c
│   ├── users.c
│   ├── courses.c
│   ├── database.c
│   └── sqlite3.c
│
└── README.md
```

## Database Tables

* users
* courses
* enrollments
* lessons
* lesson_progress
* reviews

## Authors

* Yahia Nasrallah

## Academic Course

Laboratory of Informatics

## Instructor

Gennaro Vessio
