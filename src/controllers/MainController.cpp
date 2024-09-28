#include "MainController.hpp"

MainController::MainController(QObject *parent)
    : QObject{parent}
    , _BPController(nullptr)
    , _BLController(nullptr)
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
    if (to == from) return;
    _win->gotoPage(to);

    switch (to) {
    case MainWindow::WELCOME:
        stopBookingProcess();
        stopBookingListProcess();
        break;
    case MainWindow::BOOKING:
        stopBookingListProcess();
        initBookingProcess();
        break;
    case MainWindow::LIST:
        stopBookingProcess();
        initBookingListProcess();
        break;
    }
}


void MainController::performModif(Booking booking, Client client)
{
    changePage(MainWindow::LIST, MainWindow::BOOKING);
    _BPController->setBooking(booking);
    _BPController->setClient(client);
    _BPController->toUpdatingState();
}

