#include "Client.hpp"

Client::Client()
    : Entity()
{
    _deleteSttm = "DELETE FROM CLIENT WHERE NUMCLI=:num";
    _insertSttm = "INSERT INTO CLIENT (:num, :nom, :adr, :sexe, :tel)";
    _selectSttm = "SELECT FROM CLIENT WHERE NUM=:num";
    _updateSttm = "UPDATE CLIENT SET NOM=:nom, ADRESSE=:adr,"
                  "SEXE=:sexe, TEL=:tel WHERE NUM=:num";
    _getIdSttm = "SELECT MAX(NUMCLI) FROM CLIENT";
}


qint32 Client::getNum() const
{
    return _num;
}

void Client::setNum(qint32 num)
{
    _num = num;
}

QString Client::getNom() const
{
    return _nom;
}

void Client::setNom(const QString &nom)
{
    _nom = nom;
}

QString Client::getAdresse() const
{
    return _adresse;
}

void Client::setAdresse(const QString &adresse)
{
    _adresse = adresse;
}

QString Client::getTelephone() const
{
    return _telephone;
}

void Client::setTelephone(const QString &telephone)
{
    _telephone = telephone;
}

Sexe Client::getSexe() const
{
    return _sexe;
}

QChar Client::getCharSexe() const
{
    if (_sexe == HOMME) return 'H';
    else return 'F';
}

void Client::setSexe(const Sexe sexe)
{
    _sexe = sexe;
}
