#include "BookingView.hpp"
#include "ui_BookingView.h"

BookingView::BookingView(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::BookingView)
{
    ui->setupUi(this);
    setAvanceSync();
    setDateValue();
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


void BookingView::setBooking(Booking booking)
{
    _booking = booking;
    ui->dateDep->setDate(_booking.getDateDep());
    ui->placeIn->setValue(_booking.getNumPlace());
    ui->avanceIn->setValue(_booking.getAvance());
}


void BookingView::setAvanceSync()
{
    connect(ui->avanceIn, SIGNAL(valueChanged(int)),
            this, SLOT(syncReste(qint32)));
}


void BookingView::setDateValue()
{
    ui->dateDep->setDate(QDate::currentDate());
}


void BookingView::syncReste(qint32 avance)
{
    qint32 total = 50000;
    qint32 reste = total - avance;
    ui->resteFraiDisp->display(QString::number(reste));
}
