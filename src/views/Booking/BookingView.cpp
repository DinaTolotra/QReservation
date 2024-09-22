#include "BookingView.hpp"
#include "ui_BookingView.h"

BookingView::BookingView(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::BookingView)
{
    ui->setupUi(this);
}

BookingView::~BookingView()
{
    delete ui;
}
