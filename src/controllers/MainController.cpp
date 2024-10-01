#include "MainController.hpp"

MainController::MainController(QObject *parent)
    : QObject{parent}
    , _BPController(nullptr)
    , _BLController(nullptr)
    , _clientListController(nullptr)
{
    Database::setupDatabase();
    createWindow();
    setupConnection();
}


MainController::~MainController()
{
    if (_BPController != nullptr)
        delete _BPController;
    Database::closeDatabase();
}


void MainController::exec()
{
    _win->show();
}


bool MainController::createWindow()
{
    _win = new MainWindow();
    bool ok = _win != nullptr;
    return ok;
}


void MainController::setupConnection()
{
    connect(_win, &MainWindow::requestPageChange,
            this, &MainController::changePage);
}


void MainController::changePage(MainWindow::Page from, MainWindow::Page to)
{
    _win->gotoPage(to);

    switch (from) {
    case MainWindow::WELCOME:
        // nothing here
        break;
    case MainWindow::BOOKING:
        stopBookingProcess();
        break;
    case MainWindow::BOOKINGLIST:
        stopBookingListProcess();
        break;
    case MainWindow::CLIENTLIST:
        stopClientList();
        break;
    }

    switch (to) {
    case MainWindow::WELCOME:
        // nothing here
        break;
    case MainWindow::BOOKING:
        initBookingProcess();
        break;
    case MainWindow::BOOKINGLIST:
        initBookingListProcess();
        break;
    case MainWindow::CLIENTLIST:
        initClientList();
        break;
    }
}


void MainController::performModif(Booking booking, Client client)
{
    changePage(MainWindow::BOOKINGLIST, MainWindow::BOOKING);
    _BPController->setBooking(booking);
    _BPController->setClient(client);
    _BPController->toUpdatingState();
}


void MainController::performBooking(Client client)
{
    changePage(MainWindow::CLIENTLIST, MainWindow::BOOKING);
    _BPController->setClient(client);
    _BPController->toAddingState();
}
