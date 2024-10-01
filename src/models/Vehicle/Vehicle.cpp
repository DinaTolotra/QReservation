#include "Vehicle.hpp"

QString Vehicle::_getListSttm = "SELECT * FROM VEHICULE";

Vehicle::Vehicle()
{
    _insertSttm = "INSERT INTO VEHICULE VALUE (:num, :nbPlace)";
    _selectSttm = "SELECT * FROM VEHICULE WHERE NUMVEH = :num";
    _updateSttm = "UPDATE VEHICULE SET NBPLACE=:nbPlace "
                  "WHERE NUMVEH = :num";
    _deleteSttm = "DELETE FROM VEHICULE WHERE NUMVEH=:num";
    _getFreePlaceSttm = "SELECT V.NBPLACE - COUNT(1) AS DISPO "
                        "FROM VEHICULE V "
                        "INNER JOIN RESERVATION R "
                        "   ON R.NUMVEH = V.NUMVEH "
                        "WHERE V.NUMVEH = :num "
                        "GROUP BY V.NUMVEH";
    _getLastNumSttm = "SELECT MAX(NUMVEH) AS LASTNUM FROM VEHICULE";
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

    QVariant v_num = query->value("LASTNUM");
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
        qint32 num, nbPlace;
        Vehicle veh;

        num = query->value("NUMVEH").toInt();
        nbPlace = query->value("NBPLACE").toInt();

        veh.setNum(num);
        veh.setNbPlace(nbPlace);

        vehList[num] = veh;
    }

    return vehList;
}


bool Vehicle::isValid()
{
    return _num > 0 && getNbPlaceDispo() > 0;
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

    bool ok = query->exec();

    if (!ok) qDebug() << query->lastError();

    return ok;
}


bool Vehicle::deleteDB()
{
    Database db;
    auto *query = db.getQuery();
    query->prepare(_deleteSttm);
    query->bindValue(":num", _num);

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

qint32 Vehicle::getNbPlaceDispo()
{
    Database db;
    bool ok;

    auto *query = db.getQuery();
    query->prepare(_getFreePlaceSttm);
    query->bindValue(":num", _num);
    ok = query->exec();

    ok = ok && query->next();
    if (!ok)
        qDebug() << query->lastError();


    QVariant v_dispo = query->value("DISPO");
    qint32 dispo = v_dispo.toInt(&ok);

    if (ok) return dispo;
    else return _nbPlace;
}
