#include "Vehicle.hpp"

QString Vehicle::_getListSttm = "SELECT * FROM VEHICULE";

Vehicle::Vehicle()
{
    _deleteSttm = "DELETE FROM VEHICULE WHERE NUMVEH=:num";
    _insertSttm = "INSERT INTO VEHICULE VALUE (:num, :nbPlace, :nbPDispo)";
    _selectSttm = "SELECT FROM VEHICULE WHERE NUMVEH=:num";
    _updateSttm = "UPDATE VEHICULE SET NBPLACE=:nbPlace, NBPLACEDISPO=:nbPDispo"
                  "WHERE NUMVEH=:num";
    _getLastNumSttm = "SELECT MAX(NUMVEH) FROM VEHICULE";
}


qint32 Vehicle::getLastNum()
{
    Database db;
    auto *query = db.getQuery();
    query->exec(_getLastNumSttm);
    query->next();

    return query->value(0).toInt();
}


void Vehicle::syncNumIfNot()
{
    if (_num == 0) _num = getLastNum() + 1;
}


QMap<qint32, Vehicle> Vehicle::getList()
{
    QMap<qint32, Vehicle> vehList;

    Database db;
    auto *querry = db.getQuery();
    querry->exec(_getListSttm);

    while (querry->next()) {
        qint32 num, nbPlace, nbPlaceDispo;
        Vehicle veh;

        num = querry->value("NUMVEH").toInt();
        nbPlace = querry->value("NBPLACE").toInt();
        nbPlaceDispo = querry->value("NBPLACEDISPO").toInt();

        veh.setNum(num);
        veh.setNbPlace(nbPlace);
        veh.setNbPlaceDispo(nbPlaceDispo);

        vehList[num] = veh;
    }

    return vehList;
}


bool Vehicle::isValid()
{
    return _num > 0 && _nbPlaceDispo > 0;
}


bool Vehicle::addToDB()
{
    Database db;
    auto *query = db.getQuery();
    query->prepare(_insertSttm);
    query->bindValue(":num", _num);
    query->bindValue(":nbPlace", _nbPlace);
    query->bindValue(":nbPDispo", _nbPlaceDispo);

    return query->exec();
}


bool Vehicle::upadteDB()
{
    Database db;
    auto *query = db.getQuery();
    query->prepare(_updateSttm);
    query->bindValue(":num", _num);
    query->bindValue(":nbPlace", _nbPlace);
    query->bindValue(":nbPDispo", _nbPlaceDispo);

    return query->exec();
}


qint32 Vehicle::getNum() const
{
    return _num;
}

void Vehicle::setNum(qint32 num)
{
    _num = num;
}

qint32 Vehicle::getNbPlace() const
{
    return _nbPlace;
}

void Vehicle::setNbPlace(qint32 nbPlace)
{
    _nbPlace = nbPlace;
}

qint32 Vehicle::getNbPlaceDispo() const
{
    return _nbPlaceDispo;
}

void Vehicle::setNbPlaceDispo(qint32 nbPlaceDispo)
{
    _nbPlaceDispo = nbPlaceDispo;
}


void Vehicle::decrementFreePlace()
{
    if (_nbPlaceDispo > 0) _nbPlaceDispo--;
}
