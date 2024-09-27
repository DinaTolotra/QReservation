#include "Booking.hpp"

QString Booking::_getListSttm = "SELECT * FROM RESERVATION";

Booking::Booking()
{
    _insertSttm = "INSERT INTO RESERVATION VALUE"
                  "(:num, :veh, :cli, :dep, :res, :total, :avance, :place)";
    _insertDateResSttm = "INSERT INTO CALENDRIER VALUE (:res)";
    _getLastNumSttm = "SELECT MAX(NUMRES) FROM RESERVATION";
}


qint32 Booking::getLastNum()
{
    Database db;
    auto *query = db.getQuery();
    query->exec(_getLastNumSttm);
    query->next();

    return query->value(0).toInt();
}


void Booking::syncNumIfNot()
{
    if (_num == 0) _num = getLastNum() + 1;
}


QMap<qint32, Booking> Booking::getList()
{
    QMap<qint32, Booking> bookingList;

    Database db;
    auto *query = db.getQuery();
    query->exec(_getListSttm);

    while (query->next()) {
        Booking booking;

        qint32 num = query->value("NUMRES").toInt();
        qint32 numVeh = query->value("NUMVEH").toInt();
        qint32 numCli = query->value("NUMCLI").toInt();
        QDate dateDep = query->value("DATEDEPART").toDate();
        QDate dateRes = query->value("DATERES").toDate();
        qint32 frais = query->value("FRAISTOTAL").toInt();
        qint32 avance = query->value("AVANCE").toInt();
        qint32 place = query->value("NUMPLACE").toInt();

        booking.setNum(num);
        booking.setNumVeh(numVeh);
        booking.setNumClient(numCli);
        booking.setDateDep(dateDep);
        booking.setDateRes(dateRes);
        booking.setFraisTotal(frais);
        booking.setAvance(avance);
        booking.setNumPlace(place);

        bookingList[num] = booking;
    }

    return bookingList;
}


bool Booking::isValid()
{
    bool ok = true;

    ok = ok && _num > 0;
    ok = ok && _dateDep > _dateRes;

    return ok;
}


bool Booking::addToDB()
{
    Database db;
    auto *query = db.getQuery();
    query->prepare(_insertSttm);
    query->bindValue(":num", _num);
    query->bindValue(":veh", _numVeh);
    query->bindValue(":cli", _numClient);
    query->bindValue(":dep", _dateDep.toString("yy-MM-dd"));
    query->bindValue(":res", _dateRes.toString("yy-MM-dd"));
    query->bindValue(":total", _fraisTotal);
    query->bindValue(":avance", _avance);
    query->bindValue(":place", _numPlace);

    bool ok = query->exec();

    if (!ok) qDebug() << query->lastError();

    return ok;
}


bool Booking::addDateDepToDB()
{
    Database db;
    auto *query = db.getQuery();
    query->prepare(_insertDateResSttm);
    query->bindValue(":res", _dateDep.toString("yy-MM-dd"));

    bool ok = query->exec();

    if (!ok) qDebug() << query->lastError();

    return ok;
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
