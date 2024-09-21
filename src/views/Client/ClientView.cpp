#include "ClientView.hpp"
#include "ui_ClientView.h"

ClientView::ClientView(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ClientView)
{
    ui->setupUi(this);
}

ClientView::~ClientView()
{
    delete ui;
}


Client ClientView::getClient()
{
    QString nom = ui->nomIn->text();
    QString adr = ui->addrIn->text();
    qint32 i_sexe = ui->sexeIn->currentIndex();
    Sexe sexe = i_sexe == 0? HOMME: FEMME;
    QString tel = ui->telIn->text();
    tel = formatTelToMada(tel);

    _client.setNom(nom);
    _client.setAdresse(adr);
    _client.setSexe(sexe);
    _client.setTelephone(tel);

    return _client;
}


QString ClientView::formatTelToMada(QString incompletTel)
{
    incompletTel.remove(' ');
    incompletTel.push_front("+261");
    return incompletTel;
}
