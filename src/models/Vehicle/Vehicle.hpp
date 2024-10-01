#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <QtCore/QMap>
#include <QtCore/QDate>
#include "../Entity.hpp"

class Vehicle : public Entity
{
public:
    Vehicle();

    qint32 getLastNum();
    void syncNumIfNot();

    bool addToDB();
    bool deleteDB();
    static QMap<qint32, Vehicle> getList();

    bool isValid();

    QDate getDateDep();

    // Getter
    qint32 getNum() const;
    qint32 getNbPlace() const;
    qint32 getNbPlaceDispo();

    // Setter
    void setNum(qint32 num);
    void setNbPlace(qint32 nbPlace);

private:
    QString _getLastNumSttm;
    QString _getDateDepSttm;
    QString _getFreePlaceSttm;
    static QString _getListSttm;

    qint32 _num;
    qint32 _nbPlace;

};

#endif // VEHICLE_HPP
