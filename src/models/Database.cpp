#include "Database.hpp"

// setting static propriety default value
QSqlDatabase *Database::db = nullptr;
QSqlQuery *Database::query = nullptr;


Database::Database()
{}


QSqlQuery *Database::getQuerry()
{
    return query;
}


void Database::setupDatabase()
{
    if (db == nullptr)
        setupConnection();
    if (query == nullptr)
        setupQuery();
}


void Database::closeDatabase()
{
    if (query != nullptr) {
        query->clear();
        delete query;
    }
    if (db != nullptr) {
        db->close();
        db->removeDatabase("conn");
        delete db;
    }
}


bool Database::setupConnection()
{
    if (db != nullptr) return true;

    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QMYSQL", "conn");
    db->setDatabaseName("projet_fin_annee");
    db->setHostName("localhost");
    return db->open("root", "root");
}


void Database::setupQuery()
{
    query = new QSqlQuery(*db);
}
