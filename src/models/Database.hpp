#ifndef DATABASE_HPP
#define DATABASE_HPP

// Standard library
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVector>
#include <QtCore/QDebug>

// Database library
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


class Database
{
public:
    Database();

    QSqlQuery* getQuery();
    static void setupDatabase();
    static void closeDatabase();

private:
    static bool setupConnection();
    static void setupQuery();

private:
    // follow the singleton pattern
    static QSqlDatabase *db;
    static QSqlQuery *query;
};


#endif // DATABASE_HPP
