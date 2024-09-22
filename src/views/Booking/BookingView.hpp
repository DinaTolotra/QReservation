#ifndef BOOKINGVIEW_HPP
#define BOOKINGVIEW_HPP

#include <QGroupBox>

#include "src/models/Booking/Booking.hpp"


namespace Ui {
class BookingView;
}

class BookingView : public QGroupBox
{
    Q_OBJECT

public:
    explicit BookingView(QWidget *parent = nullptr);
    ~BookingView();

    Booking getBooking();

private:
    Booking _booking;
    Ui::BookingView *ui;
};

#endif // BOOKINGVIEW_HPP
