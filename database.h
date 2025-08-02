#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>

class Database {
public:
    static void connectAndInitialize();
    static void populateSampleData();

private:
    static void createTables();
    static void insertCourses();
    static void insertModules();
    static void insertLecturers();
    static void assignLecturersToModules();
    static void insertStudents();
    static void assignMarks();
};

#endif // DATABASE_H
