#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <QObject>
#include <QString>
#include <stdexcept>

#include "src/models/Database.hpp"
#include "src/views/MainWindow.hpp"
#include "ClientListController/ClientListController.hpp"
#include "BookingProcessController/BookingProcessController.hpp"
#include "BookingListProcessController/BookingListProcessController.hpp"
#include "VehicleListController/VehicleListController.hpp"


class MainController : public QObject
{
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

    void exec();

private:
    bool createWindow();
    void setupConnection();

    void initBookingProcess();
    void stopBookingProcess();
    void initBookingListProcess();
    void stopBookingListProcess();
    void initClientList();
    void stopClientList();
    void initVehicleList();
    void stopVehicleList();

    void setBookingModifHandler();
    void setClientModifHandler();

private slots:
    void changePage(MainWindow::Page from, MainWindow::Page to);
    void performModif(Booking booking, Client client);
    void performBooking(Client client);

private:
    MainWindow *_win;

    BookingProcessController *_BPController;
    BookingListProcessController *_BLController;
    ClientListController *_clientListController;
    VehicleListController *_vehListController;
};

#endif // MAINCONTROLLER_HPP
