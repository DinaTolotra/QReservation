#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QtCore/QString>
#include <QtCore/QDebug>

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

    qint32 getLastNum();

    qint32 getLastNum();

    bool addToDB();

    // Getter
    qint32 getNum() const;
    QString getNom() const;
    Sexe getSexe() const;
    QChar getCharSexe() const;
    QString getAdresse() const;
    QString getTelephone() const;

    // Setter
    void setNum(qint32 num);
    void setNom(const QString &nom);
    void setSexe(const Sexe sexe);
    void setAdresse(const QString &adresse);
    void setTelephone(const QString &telephone);

private:
    QString _getLastNumSttm;

    qint32 _num;
    QString _nom;
    Sexe _sexe;
    QString _adresse;
    QString _telephone;

};

#endif // CLIENT_HPP
