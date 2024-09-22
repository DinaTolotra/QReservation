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

Booking BookingView::getBooking()
{
    QDate dateDep = ui->dateDep->date();
    qint32 place = ui->placeIn->value();
    qint32 avance = ui->avanceIn->value();

    _booking.setDateDep(dateDep);
    _booking.setNumPlace(place);
    _booking.setAvance(avance);

    return _booking;
}
