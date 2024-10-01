#include "BookingListView.hpp"
#include "ui_BookingListView.h"

BookingListView::BookingListView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookingListView)
{
    ui->setupUi(this);
    setTableStyle();
    disableButton();
    setUserSelectionHandler();
}

BookingListView::~BookingListView()
{
    delete ui;
}


void BookingListView::setClientList(QMap<qint32, Client> list)
{
    _clientList = list;
}


void BookingListView::setBookingList(QMap<qint32, Booking> list)
{
    _bookingList = list;
}


void BookingListView::setVehicleList(QMap<qint32, Vehicle> list)
{
    _vehicleList = list;
}


void BookingListView::displayList()
{
    ui->bookingTable->clearContents();

    int row, col;
    row = col = 0;

    for (Booking booking: _bookingList) {
        qint32 num = booking.getNum();

        qint32 numCli = booking.getNumClient();
        QString nomCli;
        if (_clientList.contains(numCli))
            nomCli = _clientList[numCli].getNom();

        qint32 numVeh = booking.getNumVeh();
        QDate dateDep = booking.getDateDep();
        qint32 frais = booking.getFraisTotal();
        qint32 avance = booking.getAvance();

        ui->bookingTable->setRowCount(row+1);

        ui->bookingTable->setItem(row, col=0, new QTableWidgetItem(QString::number(num)));
        ui->bookingTable->setItem(row, ++col, new QTableWidgetItem(nomCli));
        ui->bookingTable->setItem(row, ++col, new QTableWidgetItem(QString::number(numVeh)));
        ui->bookingTable->setItem(row, ++col, new QTableWidgetItem(dateDep.toString("ddd dd/MM")));
        ui->bookingTable->setItem(row, ++col, new QTableWidgetItem(QString::number(frais)));
        ui->bookingTable->setItem(row++, ++col, new QTableWidgetItem(QString::number(avance)));
    }
}


void BookingListView::setTableStyle()
{
    auto *headerView = ui->bookingTable->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
}


void BookingListView::enableButton()
{
    ui->modifBtn->setEnabled(true);
    ui->delBtn->setEnabled(true);
}


void BookingListView::disableButton()
{
    ui->modifBtn->setEnabled(false);
    ui->delBtn->setEnabled(false);
}


qint32 BookingListView::getNumListAtRow(qint32 row)
{
    auto *numItem = ui->bookingTable->item(row, 0);
    QString str_num = numItem->text();
    return str_num.toInt();
}


void BookingListView::setUserSelectionHandler()
{
    connect(ui->bookingTable, &QTableWidget::cellDoubleClicked,
            this, &BookingListView::handleBookingSelection);
    connect(ui->modifBtn, &QPushButton::clicked,
            this, &BookingListView::sendModifRequest);
    connect(ui->delBtn, &QPushButton::clicked,
            this, &BookingListView::sendDeleteRequest);
}


void BookingListView::handleBookingSelection(qint32 row)
{
    qint32 num = getNumListAtRow(row);
    _booking = _bookingList.value(num, Booking());
    qint32 numCli = _booking.getNumClient();
    _client = _clientList.value(numCli, Client());
    enableButton();
}


void BookingListView::sendModifRequest()
{
    emit requestModificationFor(_booking, _client);
}


void BookingListView::sendDeleteRequest()
{
    emit requestDeletionFor(_booking, _client);
}
