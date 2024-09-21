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
    /**
     * @brief Constructeur par defaut
     */
    Database();

    /**
     * @brief Obtenir le querry du DB
     * @return Un pointeur vers le querry du DB
     */
    QSqlQuery* getQuerry();

    /**
     * @brief Initialise le connection avec le DB
     * @return True si le connection est etablie, False sinon
     */
    bool setupConnection();
    /**
     * @brief Initialise l'objet query
     */
    void setupQuery();

    /**
     * @brief Termine la connection
     */
    void disconnect();

private:
    // the _db instance follow the singleton pattern
    static QSqlDatabase *_db;
    static QSqlQuery *_query;
};


#endif // DATABASE_HPP
