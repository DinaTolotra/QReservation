#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <QDate>
#include <QString>

#include "src/models/Entity.hpp"


class Booking : public Entity
{
public:
    Booking();

    bool addToDB();

    qint32 getLastNum();

    // Getter
    qint32 getNum() const;
    qint32 getNumClient() const;
    qint32 getNumVeh() const;
    QDate getDateDep() const;
    QDate getDateRes() const;
    qint32 getNumPlace() const;
    float getFraisTotal() const;
    float getAvance() const;

    // Setter
    void setNum(qint32 num);
    void setDateRes(const QDate &dateRes);
    void setNumClient(qint32 numClient);
    void setNumVeh(qint32 numVeh);
    void setDateDep(const QDate &dateDep);
    void setNumPlace(qint32 NumPlace);
    void setFraisTotal(float fraisTotal);
    void setAvance(float avance);


private:
    QString _getLastNumSttm;

    qint32 _num;
    qint32 _numClient;
    qint32 _numVeh;
    QDate _dateDep;
    QDate _dateRes;
    qint32 _numPlace;
    float _fraisTotal;
    float _avance;
};

#endif // BOOKING_HPP
