#include "ClientList.hpp"
#include "ui_ClientList.h"

ClientList::ClientList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientList)
{
    ui->setupUi(this);
}

ClientList::~ClientList()
{
    delete ui;
}
