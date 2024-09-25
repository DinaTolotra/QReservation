#include "MainController.hpp"

MainController::MainController(QObject *parent)
    : QObject{parent}
    , _BPController(nullptr)
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


bool MainController::initBookingProcess()
{
    if (_win == nullptr)
        throw std::runtime_error(
            "Main window not created"
            );

    if (_BPController != nullptr)
        throw std::runtime_error(
            "Booking process controller not deleted"
            );

    _BPController = new BookingProcessController();
    _BPController->initControlFor(_win);

    bool ok = _BPController != nullptr;

    return ok;
}


bool MainController::stopBookingProcess()
{
    if (_BPController == nullptr) return false;

    delete _BPController;
    _BPController = nullptr;

    bool ok = _BPController == nullptr;

    return ok;
}


void MainController::changePage(MainWindow::Page from, MainWindow::Page to)
{
    if (to == from) return;
    _win->gotoPage(to);

    switch (to) {
    case MainWindow::WELCOME:
        stopBookingProcess();
        break;
    case MainWindow::BOOKING:
        initBookingProcess();
        break;
    }
}
