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


qint32 BookingListView::getNumListAtRow(qint32 row)
{
    auto *numItem = ui->bookingTable->itemAt(0, row);
    QString str_num = numItem->text();
    return str_num.toInt();
}


void BookingListView::setUserSelectionHandler()
{
    connect(ui->bookingTable, &QTableWidget::cellDoubleClicked,
            this, &BookingListView::handleBookingSelection);
}


void BookingListView::handleBookingSelection(qint32 row)
{
    qint32 num = getNumListAtRow(row);
    Booking selected = _bookingList[num];
    emit requestForModification(selected);
}

