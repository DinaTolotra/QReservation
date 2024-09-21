#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <QtCore/QString>

#include "Database.hpp"


class Entity
{
public:
    virtual bool addToDB() = 0;
    virtual bool updateIntoDB() = 0;
    virtual bool removeIntoDB() = 0;

protected:
    Entity();
    ~Entity();

private:
    Entity(const Entity &entity) = delete;
    Entity operator=(const Entity &entity) = delete;

protected:
    Database *_db;
    QString _selectSttm;
    QString _insertSttm;
    QString _updateSttm;
    QString _deleteSttm;

};

#endif // ENTITY_HPP
