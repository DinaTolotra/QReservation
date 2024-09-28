#ifndef BOOKINGLISTVIEW_HPP
#define BOOKINGLISTVIEW_HPP

#include <QWidget>

#include "src/models/Client/Client.hpp"
#include "src/models/Booking/Booking.hpp"
#include "src/models/Vehicle/Vehicle.hpp"


namespace Ui {
class BookingListView;
}

class BookingListView : public QWidget
{
    Q_OBJECT

public:
    explicit BookingListView(QWidget *parent = nullptr);
    ~BookingListView();

    void setClientList(QMap<qint32, Client> list);
    void setBookingList(QMap<qint32, Booking> list);
    void setVehicleList(QMap<qint32, Vehicle> list);
    void displayList();

private:
    void setTableStyle();
    qint32 getNumListAtRow(qint32 row);
    void setUserSelectionHandler();

signals:
    void requestForModification(Booking booking);

private slots:
    void handleBookingSelection(qint32 row);

private:
    Ui::BookingListView *ui;
    QMap<qint32, Booking> _bookingList;
    QMap<qint32, Client> _clientList;
    QMap<qint32, Vehicle> _vehicleList;
};

#endif // BOOKINGLISTVIEW_HPP
