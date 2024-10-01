#include "ClientList.hpp"
#include "ui_ClientList.h"

ClientList::ClientList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientList)
{
    ui->setupUi(this);
    setTableStyle();
    disableBookingBtn();
    disableDeleteBtn();
    setUserSelectionHandler();
    setSearchRequestHandler();
}

ClientList::~ClientList()
{
    delete ui;
}


void ClientList::setClientList(QMap<qint32, Client> cliList)
{
    _cliList = cliList;
}


void ClientList::displayList()
{
    ui->clientTable->clearContents();
    ui->clientTable->setRowCount(0);

    int row, col;
    row = col = 0;

    for (Client cli: _cliList) {
        qint32 num = cli.getNum();
        QString nom = cli.getNom();
        QString tel = cli.getTelephone();
        qint32 nbRes = cli.getNbRes();

        ui->clientTable->setRowCount(row+1);

        ui->clientTable->setItem(row, col=0, new QTableWidgetItem(QString::number(num)));
        ui->clientTable->setItem(row, ++col, new QTableWidgetItem(nom));
        ui->clientTable->setItem(row, ++col, new QTableWidgetItem(tel));
        ui->clientTable->setItem(row++, ++col, new QTableWidgetItem(QString::number(nbRes)));
    }
}


void ClientList::setTableStyle()
{
    auto *headerView = ui->clientTable->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
}


void ClientList::enableBookingBtn()
{
    ui->resBtn->setEnabled(true);
}

void ClientList::enableDeletBtn()
{
    ui->delBtn->setEnabled(true);
}

void ClientList::disableBookingBtn()
{
    ui->resBtn->setEnabled(false);
}

void ClientList::disableDeleteBtn()
{
    ui->delBtn->setEnabled(false);
}


void ClientList::setUserSelectionHandler()
{
    connect(ui->clientTable, &QTableWidget::cellDoubleClicked,
            this, &ClientList::handleBookingSelection);
    connect(ui->resBtn, &QPushButton::clicked,
            this, &ClientList::sendBookingRequest);
    connect(ui->delBtn, &QPushButton::clicked,
            this, &ClientList::sendDeleteRequest);
}


void ClientList::setSearchRequestHandler()
{
    connect(ui->searchBtn, &QPushButton::clicked,
            this, &ClientList::handleSearchRequest);
}


qint32 ClientList::getNumListAtRow(qint32 row)
{
    auto *numItem = ui->clientTable->item(row, 0);
    QString str_num = numItem->text();
    return str_num.toInt();
}


void ClientList::handleBookingSelection(qint32 row)
{
    qint32 num = getNumListAtRow(row);
    _client = _cliList.value(num);
    qint32 nbRes = _client.getNbRes();
    enableBookingBtn();
    if (nbRes == 0)
        enableDeletBtn();
}


void ClientList::sendBookingRequest()
{
    emit requestBookingFor(_client);
}


void ClientList::sendDeleteRequest()
{
    emit requestDeletionFor(_client);
}


void ClientList::handleSearchRequest()
{
    QString name = ui->searchIn->text();
    emit requestNameFilter(name);
}
