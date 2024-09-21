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
     * @brief Execute un commande sql
     * @param sttm Le commande à exectuer
     * @return True si l'execution s'est bien passée, False sinon
     */
    bool exec(QString sttm);
    /**
     * @brief Obtenir la valeur d'un colonne donnée
     * @param colName
     * @return
     */
    QVariant value(QString colName);
    /**
     * @brief Passe à l'enregitrement suivant
     * @return True si il y a encore un ou plusieur enregistrements
     */
    bool next();

    /**
     * @brief Initialise le connection avec le DB
     * @return
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
    QSqlQuery *_query;
};


#endif // DATABASE_HPP
