#ifndef BOOKINGLISTVIEW_HPP
#define BOOKINGLISTVIEW_HPP

#include <QWidget>
#include <QTableWidgetItem>

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
    void enableButton();
    void disableButton();
    void setUserSelectionHandler();
    qint32 getNumListAtRow(qint32 row);

signals:
    void requestModificationFor(Booking booking, Client client);
    void requestDeletionFor(Booking booking, Client client);

private slots:
    void handleBookingSelection(qint32 row);
    void sendModifRequest();
    void sendDeleteRequest();

private:
    Ui::BookingListView *ui;
    Client _client;
    Booking _booking;
    QMap<qint32, Booking> _bookingList;
    QMap<qint32, Client> _clientList;
    QMap<qint32, Vehicle> _vehicleList;
};

#endif // BOOKINGLISTVIEW_HPP
