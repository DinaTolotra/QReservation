#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QtCore/QString>

#include "../Entity.hpp"


enum Sexe {
    HOMME, FEMME
};


class Client : public Entity
{
public:
    Client();

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
    QString _getIdSttm;

    qint32 _num;
    QString _nom;
    Sexe _sexe;
    QString _adresse;
    QString _telephone;

};

#endif // CLIENT_HPP
