#include "Client.hpp"

Client::Client()
    : Entity()
    , _num(0)
{
    _deleteSttm = "DELETE FROM CLIENT WHERE NUMCLI=:num";
    _insertSttm = "INSERT INTO CLIENT VALUE (:num, :nom, :sexe, :adr, :tel)";
    _selectSttm = "SELECT FROM CLIENT WHERE NUM=:num";
    _updateSttm = "UPDATE CLIENT SET NOM=:nom, ADRESSE=:adr,"
                  "SEXE=:sexe, TEL=:tel WHERE NUM=:num";
    _getLastNumSttm = "SELECT MAX(NUMCLI) FROM CLIENT";
}


qint32 Client::getLastNum()
{
    auto *query = _db->getQuerry();
    query->exec(_getLastNumSttm);
    query->next();

    return query->value(0).toInt();
}


bool Client::addToDB()
{
    if (_num == 0) _num = getLastNum() + 1;

    auto *query = _db->getQuerry();
    query->prepare(_insertSttm);
    query->bindValue(":num", _num);
    query->bindValue(":nom", _nom);
    query->bindValue(":adr", _adresse);
    query->bindValue(":sexe", sexeToChar(_sexe));
    query->bindValue(":tel", _telephone);

    return query->exec();
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



QChar sexeToChar(Sexe sexe)
{
    return sexe == HOMME? 'H': 'F';
}

Sexe charToSexe(QChar c_sexe)
{
    return c_sexe == 'H'? HOMME: FEMME;
}
