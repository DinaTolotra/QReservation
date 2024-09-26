#ifndef BOOKINGPROCESS_HPP
#define BOOKINGPROCESS_HPP

#include <QStackedWidget>

#include "src/models/Client/Client.hpp"
#include "src/models/Booking/Booking.hpp"
#include "src/models/Vehicle/Vehicle.hpp"


namespace Ui {
class BookingProcess;
}

class BookingProcess : public QStackedWidget
{
    Q_OBJECT

public:
    enum Page {
        BOOKING = 0,
        CLIENT = 1,
        VEHICLE = 2
    };

public:
    explicit BookingProcess(QWidget *parent = nullptr);
    ~BookingProcess();

    void gotoPage(Page page);

    Booking getBooking();
    Client getClient();
    Vehicle getVehicle();

    void setVehicleData(QMap<qint32, Vehicle> vehList);
    void displayVehicleList();

private:
    void setPageChangeEventHandler();

signals:
    void requestPageChange(Page from, Page to);
    void saveBookingRequest();

private:
    Ui::BookingProcess *ui;
    Page _currentPage;
};

#endif // BOOKINGPROCESS_HPP
