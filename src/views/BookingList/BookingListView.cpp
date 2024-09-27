#include "BookingListView.hpp"
#include "ui_BookingListView.h"

BookingListView::BookingListView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookingListView)
{
    ui->setupUi(this);
    setTableStyle();
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

        qint32 numPlace = booking.getNumPlace();
        qint32 frais = booking.getFraisTotal();
        qint32 avance = booking.getAvance();

        ui->bookingTable->setRowCount(row+1);

        ui->bookingTable->setItem(row, col=0, new QTableWidgetItem(QString::number(num)));
        ui->bookingTable->setItem(row, ++col, new QTableWidgetItem(nomCli));
        ui->bookingTable->setItem(row, ++col, new QTableWidgetItem(QString::number(numPlace)));
        ui->bookingTable->setItem(row, ++col, new QTableWidgetItem(QString::number(frais)));
        ui->bookingTable->setItem(row++, ++col, new QTableWidgetItem(QString::number(avance)));
    }
}


void BookingListView::setTableStyle()
{
    auto *headerView = ui->bookingTable->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
}
