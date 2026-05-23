#ifndef REVIEWS_H
#define REVIEWS_H


/*
====================================
Review Structure

Stores review information
====================================
*/
typedef struct {

    int id;

    char studentUsername[50];

    int courseId;

    int rating;

    char comment[255];

} Review;

/* =================================
            FUNCTIONS
================================= */

void addReview();
void viewReviews();

#endif