#include "BookingProcess.hpp"
#include "ui_BookingProcess.h"

BookingProcess::BookingProcess(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::BookingProcess)
    , _currentPage(BOOKING)
{
    ui->setupUi(this);
    setPageChangeEventHandler();
    gotoPage(_currentPage);
}


BookingProcess::~BookingProcess()
{
    delete ui;
}


void BookingProcess::gotoPage(Page page)
{
    switch (page) {
    case BOOKING:
        // do nothing
        break;
    case CLIENT:
        // do nothing
        break;
    case VEHICLE:
        ui->vehicleForm->displayList();
        break;
    }

    this->setCurrentIndex(page);
    _currentPage = page;
}


void BookingProcess::setBooking(Booking booking)
{
    ui->bookingForm->setBooking(booking);
}


void BookingProcess::setClient(Client client)
{
    ui->clientForm->setClient(client);
}


Booking BookingProcess::getBooking()
{
    return ui->bookingForm->getBooking();
}

Client BookingProcess::getClient()
{
    return ui->clientForm->getClient();
}

Vehicle BookingProcess::getVehicle()
{
    return ui->vehicleForm->getVehicle();
}


void BookingProcess::setVehicleData(QMap<qint32, Vehicle> vehList)
{
    ui->vehicleForm->setVehicleList(vehList);
}


void BookingProcess::displayVehicleList()
{
    ui->vehicleForm->displayList();
}


void BookingProcess::setPageChangeEventHandler()
{
    connect(ui->resNextBtn, &QPushButton::clicked, [this]() -> void {
        emit this->requestPageChange(this->_currentPage, CLIENT);
    });
    connect(ui->cliNextBtn, &QPushButton::clicked, [this]() -> void {
        emit this->requestPageChange(this->_currentPage, VEHICLE);
    });
    connect(ui->saveBtn, &QPushButton::clicked,
            this, &BookingProcess::saveBookingRequest);
}




