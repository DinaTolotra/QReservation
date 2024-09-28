#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <QtCore/QString>

#include "Database.hpp"


class Entity
{
public:
    virtual bool addToDB() = 0;

protected:
    Entity();

protected:
    QString _selectSttm;
    QString _insertSttm;
    QString _updateSttm;
    QString _deleteSttm;

};

#endif // ENTITY_HPP
