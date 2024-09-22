#include "Booking.hpp"

Booking::Booking()
{
    _insertSttm = "INSERT INTO RESERVATION VALUE"
                  "(:num, :veh, :cli, :dep, :res, :total, :avance, :place)";
    _getLastNumSttm = "SELECT MAX(NUMCLI) FROM RESERVATION";
}


qint32 Booking::getLastNum()
{
    Database db;
    auto *query = db.getQuerry();
    query->exec(_getLastNumSttm);
    query->next();

    return query->value(0).toInt();
}


bool Booking::addToDB()
{
    if (_num == 0) _num = getLastNum() + 1;

    Database db;
    auto *query = db.getQuerry();
    query->prepare(_insertSttm);
    query->bindValue(":num", _num);
    query->bindValue(":veh", _numVeh);
    query->bindValue(":cli", _numClient);
    query->bindValue(":dep", _dateDep.toString("yy-mm-dd"));
    query->bindValue(":res", _dateRes.toString("yy-mm-dd"));
    query->bindValue(":total", _fraisTotal);
    query->bindValue(":avance", _avance);
    query->bindValue(":place", _numPlace);

    return query->exec();
}


qint32 Booking::getNum() const
{
    return _num;
}

void Booking::setNum(qint32 num)
{
    _num = num;
}

QDate Booking::getDateRes() const
{
    return _dateRes;
}

void Booking::setDateRes(const QDate &dateRes)
{
    _dateRes = dateRes;
}

qint32 Booking::getNumClient() const
{
    return _numClient;
}

void Booking::setNumClient(qint32 numClient)
{
    _numClient = numClient;
}

QDate Booking::getDateDep() const
{
    return _dateDep;
}

void Booking::setDateDep(const QDate &dateDep)
{
    _dateDep = dateDep;
}

float Booking::getFraisTotal() const
{
    return _fraisTotal;
}

void Booking::setFraisTotal(float fraisTotal)
{
    _fraisTotal = fraisTotal;
}

float Booking::getAvance() const
{
    return _avance;
}

void Booking::setAvance(float avance)
{
    _avance = avance;
}

qint32 Booking::getNumVeh() const
{
    return _numVeh;
}

void Booking::setNumVeh(qint32 numVeh)
{
    _numVeh = numVeh;
}

qint32 Booking::getNumPlace() const
{
    return _numPlace;
}

void Booking::setNumPlace(qint32 NumPlace)
{
    _numPlace = NumPlace;
}
