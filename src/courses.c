/*
=========================================
Learning Management System
Course Management Module

This file handles:
- Course management
- Lesson management
- Student enrollments
- Progress tracking
- Reviews system
=========================================
*/


/* =================================
            LIBRARIES
================================= */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "../include/sqlite3.h"
#include "../include/courses.h"
#include "../include/users.h"

/* =================================
        GLOBAL VARIABLES
================================= */
extern char currentUsername[50];

static int enrollmentFound = 0;

static int lessonCompleted = 0;
static int lessonFound = 0;

static int courseFound = 0;

static int studentCount = 0;

int recordsFound = 0;

/* =================================
            CALLBACKS
================================= */

int reviewsCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    static char lastCourse[100] = "";

    if(strcmp(lastCourse, argv[0]) != 0) {

        printf("\n===== %s =====\n", argv[0]);

        strcpy(lastCourse, argv[0]);
    }

    printf("\nStudent: %s\n", argv[1]);

    printf("Rating: %s/5\n", argv[2]);

    printf("Comment: %s\n", argv[3]);

    return 0;
}

int checkCourseExistsCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    courseFound = 1;

    return 0;
}

int progressCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    recordsFound = 1;

    int totalLessons = atoi(argv[2]);

    int completedLessons = atoi(argv[3]);

    int progress = 0;

    if(totalLessons > 0) {

        progress =
            (completedLessons * 100) / totalLessons;
    }

    printf("\nCourse: %s\n", argv[1]);

    printf(
        "Completed Lessons: %d/%d\n",
        completedLessons,
        totalLessons
    );

    printf("Progress: %d%%\n", progress);

    return 0;
}
int checkLessonExistsCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    lessonFound = 1;

    return 0;
}

int checkLessonProgressCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    lessonCompleted = 1;

    return 0;
}

int lessonContentCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    printf("\n===== LESSON CONTENT =====\n");

    printf("Lesson: %s\n", argv[2]);

    printf("\nContent:\n%s\n", argv[3]);

    return 0;
}

int lessonsCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[500];

    lessonCompleted = 0;

    sprintf(
        sql,
        "SELECT * FROM lesson_progress "
        "WHERE student_username='%s' "
        "AND lesson_id=%s;",
        currentUsername,
        argv[0]
    );

    sqlite3_exec(
        db,
        sql,
        checkLessonProgressCallback,
        0,
        0
    );

    if(lessonCompleted) {

        printf("   [DONE] [%s] %s\n", argv[0], argv[2]);
    } else {

        printf("   [NOT DONE] [%s] %s\n", argv[0], argv[2]);
    }

    sqlite3_close(db);

    return 0;
}

int teacherLessonsCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    printf("   [%s] %s\n", argv[0], argv[2]);

    return 0;
}

int countStudentsCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    studentCount = atoi(argv[0]);

    return 0;
}

int viewCoursesCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {
    recordsFound = 1;
    printf("\nCourse ID: %s\n", argv[0]);
    printf("Title: %s\n", argv[1]);
    printf("Description: %s\n", argv[2]);
    printf("Category: %s\n", argv[3]);

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[500];

    studentCount = 0;

    sprintf(
        sql,
        "SELECT COUNT(*) "
        "FROM enrollments "
        "WHERE course_id=%s;",
        argv[0]
    );

    sqlite3_exec(
        db,
        sql,
        countStudentsCallback,
        0,
        0
    );

    printf("Enrolled Students: %d\n", studentCount);

    sprintf(
        sql,
        "SELECT * FROM lessons "
        "WHERE course_id=%s;",
        argv[0]
    );

    printf("\033[1;36mLessons:\033[0m\n");

    sqlite3_exec(
        db,
        sql,
        teacherLessonsCallback,
        0,
        0
    );

    sqlite3_close(db);

    return 0;
}

int enrollmentCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    enrollmentFound = 1;

    return 0;
}

int enrolledStudentsCallback(
    void *NotUsed,
    int argc,
    char **argv,
    char **azColName
) {

    static char lastCourse[100] = "";

    if(strcmp(lastCourse, argv[0]) != 0) {

        printf("\n===== %s =====\n", argv[0]);

        strcpy(lastCourse, argv[0]);
    }

    printf("- %s\n", argv[1]);

    return 0;
}



/* =================================
        COURSE FUNCTIONS
================================= */

void addCourse() {

    Course newCourse;

    int categoryChoice;

    printf("\n===== ADD COURSE =====\n");
    getchar();
    printf("Enter course title: ");
    scanf(" %[^\n]", newCourse.title);

    printf("Enter course description: ");
    scanf(" %[^\n]", newCourse.description);

   printf("\nSelect category:\n");

printf("1. Programming\n");
printf("2. Artificial Intelligence\n");
printf("3. Web Development\n");
printf("4. Cyber Security\n");
printf("5. Data Science\n");

while(1) {

    printf("\nChoose category (1-5): ");

    if(scanf("%d", &categoryChoice) != 1) {

        printf(
            "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
        );

        while(getchar() != '\n');

        continue;
    }

    if(categoryChoice < 1 || categoryChoice > 5) {

        printf(
            "\n\033[1;31mInvalid category! Choose between 1 and 5.\033[0m\n"
        );

        continue;
    }

    break;
}

switch(categoryChoice) {

    case 1:
        strcpy(newCourse.category, "Programming");
        break;

    case 2:
        strcpy(newCourse.category, "Artificial Intelligence");
        break;

    case 3:
        strcpy(newCourse.category, "Web Development");
        break;

    case 4:
        strcpy(newCourse.category, "Cyber Security");
        break;

    case 5:
        strcpy(newCourse.category, "Data Science");
        break;
}

    printf("\nCourse Data:\n");

    printf("Title: %s\n", newCourse.title);
    printf("Description: %s\n", newCourse.description);
    printf("Category: %s\n", newCourse.category);

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[1000];

    sprintf(
    sql,
    "INSERT INTO courses "
    "(title, description, category, teacher_username) "
    "VALUES ('%s', '%s', '%s', '%s');",
        newCourse.title,
        newCourse.description,
        newCourse.category,
        currentUsername
    );

    sqlite3_exec(db, sql, 0, 0, 0);

    printf("\n\033[1;32mCourse added successfully!\033[0m\n");

    sqlite3_close(db);


}

void viewMyCourses() {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    recordsFound = 0;

    char sql[500];

    sprintf(
        sql,
        "SELECT * FROM courses "
        "WHERE teacher_username='%s';",
        currentUsername
    );

    printf("\n===== MY COURSES =====\n");

    sqlite3_exec(db, sql, viewCoursesCallback, 0, 0);

    if(!recordsFound) {

        printf(
            "\n\033[1;31mNo courses found.\033[0m\n"
        );
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    sqlite3_close(db);
}

void viewAllCourses() {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    recordsFound = 0;

    char *sql = "SELECT * FROM courses;";

    printf("\n===== ALL COURSES =====\n");

    sqlite3_exec(db, sql, viewCoursesCallback, 0, 0);

    if(!recordsFound) {

        printf(
            "\n\033[1;31mNo courses available.\033[0m\n"
        );
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    sqlite3_close(db);
}

void editCourse() {

    int courseId;
    int editChoice;

    char newValue[300];

    printf("\n===== EDIT COURSE =====\n");

    viewMyCourses();

    while(1) {

        printf("\nEnter Course ID: ");

        if(scanf("%d", &courseId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Course ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(courseId <= 0) {

            printf(
                "\n\033[1;31mInvalid Course ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    printf("\nWhat do you want to edit?\n");

    printf("1. Title\n");
    printf("2. Description\n");
    printf("3. Category\n");
    printf("0. Cancel\n");

    while(1) {

        printf("\nChoose option (0-3): ");

        if(scanf("%d", &editChoice) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(editChoice == 0) {

            printf(
                "\n\033[1;33mEdit operation cancelled.\033[0m\n"
            );

            return;
        }

        if(editChoice < 1 || editChoice > 3) {

            printf(
                "\n\033[1;31mInvalid option! Choose between 0 and 3.\033[0m\n"
            );

            continue;
        }

        break;
    }

    getchar();

    printf("Enter new value: ");
    scanf(" %[^\n]", newValue);

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[1000];

    if(editChoice == 1) {

        sprintf(
            sql,
            "UPDATE courses "
            "SET title='%s' "
            "WHERE id=%d "
            "AND teacher_username='%s';",
            newValue,
            courseId,
            currentUsername
        );

    } else if(editChoice == 2) {

        sprintf(
            sql,
            "UPDATE courses "
            "SET description='%s' "
            "WHERE id=%d "
            "AND teacher_username='%s';",
            newValue,
            courseId,
            currentUsername
        );

    } else {

        sprintf(
            sql,
            "UPDATE courses "
            "SET category='%s' "
            "WHERE id=%d "
            "AND teacher_username='%s';",
            newValue,
            courseId,
            currentUsername
        );
    }

    sqlite3_exec(db, sql, 0, 0, 0);

    if(sqlite3_changes(db) == 0) {

        printf(
            "\n\033[1;31mCourse not found.\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    printf(
        "\n\033[1;32mCourse updated successfully!\033[0m\n"
    );

    sqlite3_close(db);
}

void deleteCourse() {

    int courseId;

    char confirm;

    printf("\n===== DELETE COURSE =====\n");

    viewMyCourses();

    while(1) {

        printf("\nEnter Course ID to delete (0 to cancel): ");

        if(scanf("%d", &courseId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Course ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(courseId == 0) {

            printf(
                "\n\033[1;33mDelete operation cancelled.\033[0m\n"
            );

            return;
        }

        if(courseId < 0) {

            printf(
                "\n\033[1;31mInvalid Course ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    getchar();

    printf(
        "\n\033[1;31mWARNING:\033[0m "
        "Deleting this course will remove it "
        "for all enrolled students.\n"
    );

    printf("Type 'y' to confirm deletion: ");
    scanf("%c", &confirm);

    if(confirm != 'y' && confirm != 'Y') {

        printf(
            "\n\033[1;33mDeletion cancelled.\033[0m\n"
        );

        return;
    }

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[500];

    sprintf(
        sql,
        "DELETE FROM courses "
        "WHERE id=%d "
        "AND teacher_username='%s';",
        courseId,
        currentUsername
    );

    sqlite3_exec(db, sql, 0, 0, 0);

    if(sqlite3_changes(db) == 0) {

        printf(
            "\n\033[1;31mCourse not found.\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    sprintf(
        sql,
        "DELETE FROM enrollments "
        "WHERE course_id=%d;",
        courseId
    );

    sqlite3_exec(db, sql, 0, 0, 0);

    printf(
        "\n\033[1;32mCourse deleted successfully!\033[0m\n"
    );

    sqlite3_close(db);
}

void searchCourses() {

    sqlite3 *db;

    char keyword[100];

    int choice;

    while(1) {

        printf("\n===== SEARCH COURSES =====\n");

        getchar();

        printf("Enter keyword: ");
        scanf(" %[^\n]", keyword);

        sqlite3_open("database/courses.db", &db);

        recordsFound = 0;

        char sql[1000];

        sprintf(
            sql,
            "SELECT * FROM courses "
            "WHERE title LIKE '%%%s%%';",
            keyword
        );

        printf("\n===== SEARCH RESULTS =====\n");

        sqlite3_exec(db, sql, viewCoursesCallback, 0, 0);

        if(!recordsFound) {

            printf(
                "\n\033[1;31mNo courses found.\033[0m\n"
            );
        }

        sqlite3_close(db);

        while(1) {

            printf("\n1. Search Again\n");
            printf("2. Exit Search\n");

            printf("\nChoose option (1-2): ");

            if(scanf("%d", &choice) != 1) {

                printf(
                    "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
                );

                while(getchar() != '\n');

                continue;
            }

            if(choice < 1 || choice > 2) {

                printf(
                    "\n\033[1;31mInvalid option! Choose 1 or 2.\033[0m\n"
                );

                continue;
            }

            break;
        }

        if(choice == 2) {

            printf(
                "\n\033[1;33mSearch closed.\033[0m\n"
            );

            return;
        }
    }
}

void enrollInCourse() {

    int courseId;

    printf("\n===== ENROLL IN COURSE =====\n");

    while(1) {

        printf("\nEnter Course ID (0 to cancel): ");

        if(scanf("%d", &courseId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Course ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(courseId == 0) {

            printf(
                "\n\033[1;33mEnrollment cancelled.\033[0m\n"
            );

            return;
        }

        if(courseId < 0) {

            printf(
                "\n\033[1;31mInvalid Course ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    courseFound = 0;

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[500];

    sprintf(
        sql,
        "SELECT * FROM courses "
        "WHERE id=%d;",
        courseId
    );

    sqlite3_exec(
        db,
        sql,
        checkCourseExistsCallback,
        0,
        0
    );

    if(!courseFound) {

        printf(
            "\n\033[1;31mCourse does not exist!\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    if(enrollmentExists(courseId)) {

        printf(
            "\n\033[1;31mAlready enrolled in this course!\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    sprintf(
        sql,
        "INSERT INTO enrollments "
        "(student_username, course_id, progress) "
        "VALUES ('%s', %d, 0);",
        currentUsername,
        courseId
    );

    sqlite3_exec(db, sql, 0, 0, 0);

    printf(
        "\n\033[1;32mEnrollment successful!\033[0m\n"
    );

    sqlite3_close(db);
}

void viewStudentCourses() {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    recordsFound = 0;

    char sql[1000];

    sprintf(
        sql,
        "SELECT courses.id, courses.title, "
        "courses.description, courses.category "
        "FROM courses "
        "JOIN enrollments "
        "ON courses.id = enrollments.course_id "
        "WHERE enrollments.student_username='%s';",
        currentUsername
    );

    printf("\n===== MY ENROLLED COURSES =====\n");

    sqlite3_exec(db, sql, viewCoursesCallback, 0, 0);

    if(!recordsFound) {

        printf(
            "\n\033[1;31mYou are not enrolled in any courses.\033[0m\n"
        );
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    sqlite3_close(db);
}

int enrollmentExists(int courseId) {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    enrollmentFound = 0;

    char sql[500];

    sprintf(
        sql,
        "SELECT * FROM enrollments "
        "WHERE student_username='%s' "
        "AND course_id=%d;",
        currentUsername,
        courseId
    );

    sqlite3_exec(db, sql, enrollmentCallback, 0, 0);

    sqlite3_close(db);

    return enrollmentFound;
}

void viewEnrolledStudents() {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    recordsFound = 0;

    char sql[1000];

    sprintf(
        sql,
        "SELECT courses.title, enrollments.student_username "
        "FROM courses "
        "JOIN enrollments "
        "ON courses.id = enrollments.course_id "
        "WHERE courses.teacher_username='%s' "
        "ORDER BY courses.title;",
        currentUsername
    );

    printf("\n===== ENROLLED STUDENTS =====\n");

    sqlite3_exec(db, sql, enrolledStudentsCallback, 0, 0);

    if(!recordsFound) {

        printf(
            "\n\033[1;31mNo enrolled students found.\033[0m\n"
        );
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    sqlite3_close(db);
}
/* =================================
        LESSON FUNCTIONS
================================= */

void addLesson() {

    int choice;

    printf("\n===== ADD LESSON =====\n");

    viewMyCourses();

    while(1) {

        printf("\n1. Add Lesson\n");
        printf("2. Exit\n");

        printf("\nChoose option (1-2): ");

        if(scanf("%d", &choice) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(choice < 1 || choice > 2) {

            printf(
                "\n\033[1;31mInvalid option! Choose 1 or 2.\033[0m\n"
            );

            continue;
        }

        break;
    }

    if(choice == 2) {

        printf(
            "\n\033[1;33mOperation cancelled.\033[0m\n"
        );

        return;
    }

    int courseId;

    char lessonTitle[100];
    char lessonContent[500];

    while(1) {

        printf("\nEnter Course ID (0 to cancel): ");

        if(scanf("%d", &courseId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Course ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(courseId == 0) {

            printf(
                "\n\033[1;33mOperation cancelled.\033[0m\n"
            );

            return;
        }

        if(courseId < 0) {

            printf(
                "\n\033[1;31mInvalid Course ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    getchar();

    printf("Enter lesson title: ");
    scanf(" %[^\n]", lessonTitle);

    printf("Enter lesson content: ");
    scanf(" %[^\n]", lessonContent);

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[2000];

    sprintf(
        sql,
        "INSERT INTO lessons "
        "(course_id, title, content, status) "
        "VALUES (%d, '%s', '%s', 'ACTIVE');",
        courseId,
        lessonTitle,
        lessonContent
    );

    sqlite3_exec(db, sql, 0, 0, 0);

    printf(
        "\n\033[1;32mLesson added successfully!\033[0m\n"
    );

    sqlite3_close(db);
}

void editLesson() {

    int courseId;
    int lessonId;
    int choice;

    char newValue[500];

    printf("\n===== EDIT LESSON =====\n");

    viewMyCourses();

    while(1) {

        printf("\nEnter Course ID (0 to cancel): ");

        if(scanf("%d", &courseId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Course ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(courseId == 0) {

            printf(
                "\n\033[1;33mEdit operation cancelled.\033[0m\n"
            );

            return;
        }

        if(courseId < 0) {

            printf(
                "\n\033[1;31mInvalid Course ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[2000];

    sprintf(
        sql,
        "SELECT * FROM lessons "
        "WHERE course_id=%d;",
        courseId
    );

    printf("\n===== COURSE LESSONS =====\n");

    sqlite3_exec(db, sql, lessonsCallback, 0, 0);

    while(1) {

        printf("\nEnter Lesson ID (0 to cancel): ");

        if(scanf("%d", &lessonId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Lesson ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(lessonId == 0) {

            printf(
                "\n\033[1;33mEdit operation cancelled.\033[0m\n"
            );

            sqlite3_close(db);

            return;
        }

        if(lessonId < 0) {

            printf(
                "\n\033[1;31mInvalid Lesson ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    printf("\nWhat do you want to edit?\n");

    printf("1. Lesson Title\n");
    printf("2. Lesson Content\n");
    printf("0. Cancel\n");

    while(1) {

        printf("\nChoose option (0-2): ");

        if(scanf("%d", &choice) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(choice == 0) {

            printf(
                "\n\033[1;33mEdit operation cancelled.\033[0m\n"
            );

            sqlite3_close(db);

            return;
        }

        if(choice < 1 || choice > 2) {

            printf(
                "\n\033[1;31mInvalid option! Choose between 0 and 2.\033[0m\n"
            );

            continue;
        }

        break;
    }

    getchar();

    printf("Enter new value: ");
    scanf(" %[^\n]", newValue);

    if(choice == 1) {

        sprintf(
            sql,
            "UPDATE lessons "
            "SET title='%s' "
            "WHERE id=%d;",
            newValue,
            lessonId
        );

    } else {

        sprintf(
            sql,
            "UPDATE lessons "
            "SET content='%s' "
            "WHERE id=%d;",
            newValue,
            lessonId
        );
    }

    sqlite3_exec(db, sql, 0, 0, 0);

    if(sqlite3_changes(db) == 0) {

        printf(
            "\n\033[1;31mLesson not found.\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    printf(
        "\n\033[1;32mLesson updated successfully!\033[0m\n"
    );

    sqlite3_close(db);
}

void viewLessonContent() {

    int courseId;
    int lessonId;

    printf("\n===== VIEW LESSON =====\n");

    viewStudentCourses();

    while(1) {

        printf("\nEnter Course ID (0 to Exit): ");

        if(scanf("%d", &courseId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Course ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(courseId == 0) {

            return;
        }

        if(courseId < 0) {

            printf(
                "\n\033[1;31mInvalid Course ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[1000];

    lessonFound = 0;

    sprintf(
        sql,
        "SELECT * FROM courses "
        "WHERE id=%d;",
        courseId
    );

    sqlite3_exec(
        db,
        sql,
        checkLessonExistsCallback,
        0,
        0
    );

    if(!lessonFound) {

        printf(
            "\n\033[1;31mInvalid course ID.\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    sprintf(
        sql,
        "SELECT * FROM lessons "
        "WHERE course_id=%d;",
        courseId
    );

    printf("\n===== COURSE LESSONS =====\n");

    sqlite3_exec(db, sql, lessonsCallback, 0, 0);

    while(1) {

        printf("\nEnter Lesson ID (0 to Exit): ");

        if(scanf("%d", &lessonId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Lesson ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(lessonId == 0) {

            sqlite3_close(db);

            return;
        }

        if(lessonId < 0) {

            printf(
                "\n\033[1;31mInvalid Lesson ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    lessonFound = 0;

    sprintf(
        sql,
        "SELECT * FROM lessons "
        "WHERE id=%d "
        "AND course_id=%d;",
        lessonId,
        courseId
    );

    sqlite3_exec(
        db,
        sql,
        checkLessonExistsCallback,
        0,
        0
    );

    if(!lessonFound) {

        printf(
            "\n\033[1;31mInvalid lesson ID.\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    sprintf(
        sql,
        "SELECT * FROM lessons "
        "WHERE id=%d;",
        lessonId
    );

    sqlite3_exec(db, sql, lessonContentCallback, 0, 0);

    int option;

    while(1) {

        printf("\n1. Mark as Completed\n");
        printf("2. Exit\n");

        printf("\nChoose option (1-2): ");

        if(scanf("%d", &option) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(option < 1 || option > 2) {

            printf(
                "\n\033[1;31mInvalid option! Choose 1 or 2.\033[0m\n"
            );

            continue;
        }

        break;
    }

    if(option == 1) {

        sprintf(
            sql,
            "SELECT * FROM lesson_progress "
            "WHERE student_username='%s' "
            "AND lesson_id=%d;",
            currentUsername,
            lessonId
        );

        lessonFound = 0;

        sqlite3_exec(
            db,
            sql,
            checkLessonExistsCallback,
            0,
            0
        );

        if(lessonFound) {

            printf(
                "\n\033[1;33mLesson already completed.\033[0m\n"
            );

        } else {

            sprintf(
                sql,
                "INSERT INTO lesson_progress "
                "(student_username, lesson_id, completed) "
                "VALUES ('%s', %d, 1);",
                currentUsername,
                lessonId
            );

            sqlite3_exec(db, sql, 0, 0, 0);

            printf(
                "\n\033[1;32mLesson marked as completed!\033[0m\n"
            );
        }
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    sqlite3_close(db);
}

/* =================================
        PROGRESS FUNCTIONS
================================= */

void trackProgress() {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    recordsFound = 0;

    char sql[3000];

    sprintf(
        sql,

        "SELECT courses.id, courses.title, "

        "(SELECT COUNT(*) FROM lessons "
        "WHERE lessons.course_id = courses.id), "
        "(SELECT COUNT(DISTINCT lesson_progress.lesson_id) "
        "FROM lesson_progress "
        "JOIN lessons "
        "ON lesson_progress.lesson_id = lessons.id "
        "WHERE lesson_progress.student_username='%s' "
        "AND lessons.course_id = courses.id) "

        "FROM courses "

        "JOIN enrollments "
        "ON courses.id = enrollments.course_id "

        "WHERE enrollments.student_username='%s';",

        currentUsername,
        currentUsername
    );

    printf("\n===== MY PROGRESS =====\n");

    sqlite3_exec(db, sql, progressCallback, 0, 0);

    if(!recordsFound) {

        printf(
            "\n\033[1;31mNo enrolled courses found.\033[0m\n"
        );
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    sqlite3_close(db);
}
/* =================================
        REVIEW FUNCTIONS
================================= */

void addReview() {

    int courseId;
    int rating;

    char comment[500];

    printf("\n===== ADD REVIEW =====\n");

    viewStudentCourses();

    while(1) {

        printf("\nEnter Course ID (0 to Exit): ");

        if(scanf("%d", &courseId) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a valid Course ID.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(courseId == 0) {

            return;
        }

        if(courseId < 0) {

            printf(
                "\n\033[1;31mInvalid Course ID.\033[0m\n"
            );

            continue;
        }

        break;
    }

    courseFound = 0;

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    char sql[1000];

    sprintf(
        sql,
        "SELECT * FROM courses "
        "WHERE id=%d;",
        courseId
    );

    sqlite3_exec(
        db,
        sql,
        checkCourseExistsCallback,
        0,
        0
    );

    if(!courseFound) {

        printf(
            "\n\033[1;31mInvalid course ID.\033[0m\n"
        );

        sqlite3_close(db);

        return;
    }

    while(1) {

        printf("Enter Rating (1-5): ");

        if(scanf("%d", &rating) != 1) {

            printf(
                "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
            );

            while(getchar() != '\n');

            continue;
        }

        if(rating < 1 || rating > 5) {

            printf(
                "\n\033[1;31mRating must be between 1 and 5!\033[0m\n"
            );

            continue;
        }

        break;
    }

    getchar();

    printf("Enter Comment: ");
    scanf(" %[^\n]", comment);

    sprintf(
        sql,
        "INSERT INTO reviews "
        "(student_username, course_id, rating, comment) "
        "VALUES ('%s', %d, %d, '%s');",
        currentUsername,
        courseId,
        rating,
        comment
    );

    sqlite3_exec(db, sql, 0, 0, 0);

    printf(
        "\n\033[1;32mReview added successfully!\033[0m\n"
    );

    sqlite3_close(db);
}

void viewReviews() {

    sqlite3 *db;

    sqlite3_open("database/courses.db", &db);

    recordsFound = 0;

    char sql[3000];

    sprintf(
        sql,

        "SELECT courses.title, "
        "reviews.student_username, "
        "reviews.rating, "
        "reviews.comment "

        "FROM reviews "

        "JOIN courses "
        "ON reviews.course_id = courses.id "

        "WHERE courses.teacher_username='%s' "

        "ORDER BY courses.title;",

        currentUsername
    );

    printf("\n===== COURSE REVIEWS =====\n");

    sqlite3_exec(db, sql, reviewsCallback, 0, 0);

    if(!recordsFound) {

        printf(
            "\n\033[1;31mNo reviews found.\033[0m\n"
        );
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    sqlite3_close(db);
}