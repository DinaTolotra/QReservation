#include "Database.hpp"

// setting static propriety default value
QSqlDatabase *Database::_db = nullptr;
QSqlQuery *Database::_query = nullptr;


Database::Database()
{}


bool Database::setupConnection()
{
    if (Database::_db != nullptr) return true;

    Database::_db = new QSqlDatabase();
    *Database::_db = QSqlDatabase::addDatabase("QMYSQL");
    Database::_db->setDatabaseName("projet_fin_annee");
    Database::_db->setHostName("localhost");
    return Database::_db->open("root", "root");
}


void Database::setupQuery()
{
    if (QSqlQuery::_query) return;
    QSqlQuery::_query = new QSqlQuery(*Database::_db);
}


void Database::disconnect()
{
    if (QSqlQuery::_query != nullptr) {
        QSqlQuery::_query->clear();
        delete QSqlQuery::_query;
    }
    if (Database::_db != nullptr) {
        Database::_db->close();
        delete Database::_db;
    }
}
