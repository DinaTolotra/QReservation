#include "BookingProcess.hpp"
#include "ui_BookingProcess.h"

BookingProcess::BookingProcess(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::BookingProcess)
{
    ui->setupUi(this);
}

BookingProcess::~BookingProcess()
{
    delete ui;
}
