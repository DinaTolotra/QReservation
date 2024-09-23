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
    this->setCurrentIndex(page);
    _currentPage = page;
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
