#ifndef BOOKINGLISTPROCESSCONTROLLER_HPP
#define BOOKINGLISTPROCESSCONTROLLER_HPP

#include <QObject>

#include "src/models/Database.hpp"
#include "src/models/Client/Client.hpp"
#include "src/models/Booking/Booking.hpp"
#include "src/models/Vehicle/Vehicle.hpp"

#include "src/views/MainWindow.hpp"
#include "src/views/BookingList/BookingListView.hpp"


class BookingListProcessController : public QObject
{
    Q_OBJECT
public:
    explicit BookingListProcessController(QObject *parent = nullptr);
    ~BookingListProcessController();

    void initControlFor(MainWindow *win);

    void displayList();

private:
    MainWindow *_win;
    BookingListView *_BLView;

};

#endif // BOOKINGLISTPROCESSCONTROLLER_HPP