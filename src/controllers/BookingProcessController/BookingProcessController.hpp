#ifndef BOOKINGPROCESSCONTROLLER_HPP
#define BOOKINGPROCESSCONTROLLER_HPP

#include <QObject>
#include <QString>

#include "src/models/Database.hpp"
#include "src/models/Client/Client.hpp"
#include "src/models/Booking/Booking.hpp"
#include "src/models/Vehicle/Vehicle.hpp"

#include "src/views/MainWindow.hpp"
#include "src/views/BookingProcess/BookingProcess.hpp"


class BookingProcessController : public QObject
{
    Q_OBJECT
public:
    enum State {
        CREATING,
        UPDATING
    };

public:
    explicit BookingProcessController(QObject *parent = nullptr);
    ~BookingProcessController();

    void initControlFor(MainWindow *win);

    void setBooking(Booking booking);
    void setClient(Client client);

    void toCreatingState();
    void toUpdatingState();

private:
    void setConnectionToBP();
    bool getBookingData();
    bool getClientData();

    void displayVehicleList();

    void createTicket();

private slots:
    void changePage(BookingProcess::Page from, BookingProcess::Page to);
    void saveBooking();

private:
    MainWindow *_win;
    BookingProcess *_BPView;

    State _currentState;

    Booking _booking;
    Client _client;
    Vehicle _veh;
};

#endif // BOOKINGPROCESSCONTROLLER_HPP
