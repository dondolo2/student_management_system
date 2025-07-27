#include "database.h"
#include <QSqlDatabse>
#include <QDebug>

bool Database::connect() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("student_db");
    db.setUserName("postgres");
    db.setPassword("password");

    if (!db.open()) {
        qDebug() << "Database error: " << db.lastError().text();
        return false;
    }

    qDebug() << "Connected to PostgresSQL!";
    return true;
}
