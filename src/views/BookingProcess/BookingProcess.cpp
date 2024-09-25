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
    loadViewData();
}


BookingProcess::~BookingProcess()
{
    delete ui;
}


void BookingProcess::gotoPage(Page page)
{
    this->setCurrentIndex(page);
    _currentPage = page;
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


void BookingProcess::loadViewData()
{
    auto list = Vehicle::getList();
    ui->vehicleForm->setVehicleList(list);
    ui->vehicleForm->displayList();
}

