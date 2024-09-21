#include "Database.hpp"

// setting static propriety default value
QSqlDatabase *Database::_db = nullptr;


Database::Database()
    : _query(nullptr)
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
    if (_query) return;
    _query = new QSqlQuery(*Database::_db);
}


void Database::disconnect()
{
    if (_query != nullptr) {
        _query->clear();
        delete _query;
    }
    if (Database::_db != nullptr) {
        Database::_db->close();
        delete Database::_db;
    }
}


bool Database::exec(QString sttm)
{
    _query->clear();
    return _query->exec(sttm);
}


QVariant Database::value(QString colName)
{
    if (!_query) return QVariant();
    if (!_query->isActive()) return QVariant();
    return _query->value(colName);
}


bool Database::next()
{
    if (!_query) return false;
    return _query->next();
}
