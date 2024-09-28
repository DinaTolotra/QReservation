#include "Client.hpp"

QString Client::_getListSttm = "SELECT * FROM CLIENT";

Client::Client()
    : Entity()
    , _num(0)
{
    _insertSttm = "INSERT INTO CLIENT VALUE (:num, :nom, :sexe, :adr, :tel)";
    _getLastNumSttm = "SELECT MAX(NUMCLI) FROM CLIENT";
}


qint32 Client::getLastNum()
{
    Database db;
    auto *query = db.getQuery();
    query->exec(_getLastNumSttm);
    query->next();

    bool ok;

    QVariant v_num = query->value("MAX(NUMCLI)");
    qint32 num = v_num.toInt(&ok);

    if (ok) return num;
    else return 0;
}


void Client::syncNumIfNot()
{
    if (_num == 0) _num = getLastNum() + 1;
}


QMap<qint32, Client> Client::getList()
{
    QMap<qint32, Client> clientList;

    Database db;
    auto *query = db.getQuery();
    query->exec(_getListSttm);

    while (query->next()) {
        Client client;

        qint32 num = query->value("NUMCLI").toInt();
        QString nom = query->value("NOM").toString();
        QChar c_sexe = query->value("SEXE").toString()[0];
        QString adresse = query->value("ADRESSE").toString();
        QString tel = query->value("TEL").toString();

        client.setNum(num);
        client.setNom(nom);
        client.setSexe(charToSexe(c_sexe));
        client.setAdresse(adresse);
        client.setTelephone(tel);

        clientList.insert(num, client);
    }

    return clientList;
}


bool Client::isValid()
{
    bool ok = true;

    ok = ok && _num > 0;
    ok = ok && _telephone != "+261000000000";

    return ok;
}


bool Client::addToDB()
{
    Database db;
    auto *query = db.getQuery();
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
