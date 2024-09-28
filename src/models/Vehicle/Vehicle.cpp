#include "Vehicle.hpp"

QString Vehicle::_getListSttm = "SELECT * FROM VEHICULE";

Vehicle::Vehicle()
{
    _deleteSttm = "DELETE FROM VEHICULE WHERE NUMVEH=:num";
    _insertSttm = "INSERT INTO VEHICULE VALUE (:num, :nbPlace, :nbPDispo)";
    _selectSttm = "SELECT * FROM VEHICULE WHERE NUMVEH = :num";
    _updateSttm = "UPDATE VEHICULE SET NBPLACE=:nbPlace, NBPLACEDISPO=:nbPDispo "
                  "WHERE NUMVEH = :num";
    _getLastNumSttm = "SELECT MAX(NUMVEH) FROM VEHICULE";
    _getDateDepSttm = "SELECT DATEDEPART FROM RESERVATION "
                      "WHERE NUMVEH = :num";
}


qint32 Vehicle::getLastNum()
{
    Database db;
    auto *query = db.getQuery();
    query->exec(_getLastNumSttm);
    query->next();

    bool ok;

    QVariant v_num = query->value("MAX(NUMVEH)");
    qint32 num = v_num.toInt(&ok);

    if (ok) return num;
    else return 0;
}


void Vehicle::syncNumIfNot()
{
    if (_num == 0) _num = getLastNum() + 1;
}


QMap<qint32, Vehicle> Vehicle::getList()
{
    QMap<qint32, Vehicle> vehList;

    Database db;
    auto *query = db.getQuery();
    query->exec(_getListSttm);

    while (query->next()) {
        qint32 num, nbPlace, nbPlaceDispo;
        Vehicle veh;

        num = query->value("NUMVEH").toInt();
        nbPlace = query->value("NBPLACE").toInt();
        nbPlaceDispo = query->value("NBPLACEDISPO").toInt();

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


QDate Vehicle::getDateDep()
{
    Database db;
    auto query = db.getQuery();
    query->prepare(_getDateDepSttm);
    query->bindValue(":num", _num);

    bool ok = query->exec();
    query->next();

    if (!ok) qDebug() << query->lastError();
    else return query->value("DATEDEPART").toDate();

    return QDate(0, 0, 0);
}


bool Vehicle::addToDB()
{
    Database db;
    auto *query = db.getQuery();
    query->prepare(_insertSttm);
    query->bindValue(":num", _num);
    query->bindValue(":nbPlace", _nbPlace);
    query->bindValue(":nbPDispo", _nbPlaceDispo);

    bool ok = query->exec();

    if (!ok) qDebug() << query->lastError();

    return ok;
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
