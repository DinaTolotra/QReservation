#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <QDate>
#include <QString>

#include <QSqlError>

#include "src/models/Entity.hpp"


class Booking : public Entity
{
public:
    Booking();

    bool addToDB();
    bool updateDB();
    bool deleteDB();
    bool addDateDepToDB();

    qint32 getLastNum();
    void syncNum();
    static QMap<qint32, Booking> getList();

    bool isValid();

    // Getter
    qint32 getNum() const;
    qint32 getcliNum() const;
    qint32 getNumVeh() const;
    QDate getDateDep() const;
    QDate getDateRes() const;
    qint32 getNumPlace() const;
    float getFraisTotal() const;
    float getAvance() const;

    // Setter
    void setNum(qint32 num);
    void setDateRes(const QDate &dateRes);
    void setcliNum(qint32 cliNum);
    void setNumVeh(qint32 numVeh);
    void setDateDep(const QDate &dateDep);
    void setNumPlace(qint32 NumPlace);
    void setFraisTotal(float fraisTotal);
    void setAvance(float avance);


private:
    QString _getLastNumSttm;
    static QString _getListSttm;
    QString _insertDateResSttm;

    qint32 _num;
    qint32 _cliNum;
    qint32 _numVeh;
    QDate _dateDep;
    QDate _dateRes;
    qint32 _numPlace;
    float _fraisTotal;
    float _avance;
};

#endif // BOOKING_HPP
