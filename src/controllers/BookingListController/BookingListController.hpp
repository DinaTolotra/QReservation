#ifndef BOOKINGLISTCONTROLLER_HPP
#define BOOKINGLISTCONTROLLER_HPP

#include <QObject>
#include <QRegularExpression>

#include "src/models/Database.hpp"
#include "src/models/Client/Client.hpp"
#include "src/models/Booking/Booking.hpp"
#include "src/models/Vehicle/Vehicle.hpp"

#include "src/views/MainWindow.hpp"
#include "src/views/BookingList/BookingListView.hpp"


class BookingListController : public QObject
{
    Q_OBJECT
public:
    explicit BookingListController(QObject *parent = nullptr);
    ~BookingListController();

    void initControlFor(MainWindow *win);

    void displayList();

private:
    void setChangeRequestHandler();
    void setDeleteRequestHandler();
    void setFilterRequestHandler();

signals:
    void requestModifFor(Booking booking, Client client);

private slots:
    void processDeletion(Booking booking);
    void handleFilterRequest(QString filter);

private:
    MainWindow *_win;
    BookingListView *_view;

};

#endif // BOOKINGLISTCONTROLLER_HPP
