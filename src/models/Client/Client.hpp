#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QMap>

#include "../Entity.hpp"


enum Sexe {
    HOMME, FEMME
};

QChar sexeToChar(Sexe sexe);
Sexe charToSexe(QChar c_sexe);



class Client : public Entity
{
public:
    Client();

    bool addToDB();
    bool updateDB();
    bool deleteDB();

    qint32 getLastNum();
    void syncNumIfNot();
    static QMap<qint32, Client> getList();

    bool isValid();

    // Getter
    qint32 getNum() const;
    QString getNom() const;
    Sexe getSexe() const;
    QChar getCharSexe() const;
    QString getAdresse() const;
    QString getTelephone() const;
    qint32 getNbRes() const;

    // Setter
    void setNum(qint32 num);
    void setNom(const QString &nom);
    void setSexe(const Sexe sexe);
    void setAdresse(const QString &adresse);
    void setTelephone(const QString &telephone);

private:
    QString _getLastNumSttm;
    QString _getNbResSttm;
    static QString _getListSttm;

    qint32 _num;
    QString _nom;
    Sexe _sexe;
    QString _adresse;
    QString _telephone;

};

#endif // CLIENT_HPP
