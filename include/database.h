/*
=========================================
Learning Management System
Database Header File
=========================================
*/

#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

/*
====================================
Initialize Database

Creates database tables
and connects to SQLite
====================================
*/

void initializeDatabase();

#endif