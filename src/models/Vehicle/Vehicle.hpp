#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "../Entity.hpp"

class Vehicle : public Entity
{
public:
    Vehicle();

    qint32 getLastNum();

    bool addToDB();

    // Getter
    qint32 getNum() const;
    qint32 getNbPlace() const;
    qint32 getNbPlaceDispo() const;

    // Setter
    void setNum(qint32 num);
    void setNbPlace(qint32 nbPlace);
    void setNbPlaceDispo(qint32 nbPlaceDispo);

private:
    QString _getLastNumSttm;

    qint32 _num;
    qint32 _nbPlace;
    qint32 _nbPlaceDispo;

};

#endif // VEHICLE_HPP
