/*
=========================================
Learning Management System
Main Program File

This file handles:
- Program startup
- Main menu
- Navigation between features
=========================================
*/

/* =================================
            LIBRARIES
================================= */

#include <stdio.h>

#include "../include/database.h"
#include "../include/users.h"

/* =================================
                MAIN
================================= */

int main() {

    int choice;

    /* Initialize database */
    initializeDatabase();

    /* Main program loop */
    while(1) {

        printf("\n===== COURSE PLATFORM =====\n");

        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");

       printf("\nChoose an option: ");

        if(scanf("%d", &choice) != 1) {

         printf(
        "\n\033[1;31mInvalid input! Please enter a number.\033[0m\n"
        );

        while(getchar() != '\n');

        continue;
    }

    
        switch(choice) {

            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf(
                    "\n\033[1;31mInvalid option.\033[0m\n"
                );
        }
    }

    return 0;
}