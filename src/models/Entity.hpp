#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <qt6/QtCore/QString>
#include <qt6/QtSql/QSqlDatabase>
#include <qt6/QtSql/QSqlQuery>

#include "Database.hpp"


class Entity
{
public:
    virtual Entity createFromQuery() = 0;
    virtual qint32 add(Entity entity) = 0;
    virtual bool update(Entity entity) = 0;
    virtual bool remove(Entity entity) = 0;

private:
    Entity() = delete;
    Entity(const Entity &entity) = delete;
    Entity operator=(const Entity &entity) = delete; 

private:
    Database *_db;
    QString _selectSttm;
    QString _insertSttm;
    QString _updateSttm;
    QString _deleteSttm;

};

#endif // ENTITY_HPP