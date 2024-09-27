#include "MainController.hpp"


void MainController::initBookingProcess()
{
    if (_win == nullptr)
        qDebug() << "Main window not created";
    if (_BPController != nullptr)
        qDebug() << "Booking process controller not deleted";

    _BPController = new BookingProcessController();
    _BPController->initControlFor(_win);
}

void MainController::stopBookingProcess()
{
    if (_BPController == nullptr) return;

    delete _BPController;
    _BPController = nullptr;
}


void MainController::initBookingListProcess()
{
    if (_win == nullptr)
        qDebug() << "Main window not created";
    if (_BLController != nullptr)
        qDebug() << "Booking list controller not deleted";

    _BLController = new BookingListProcessController();
    _BLController->initControlFor(_win);
    _BLController->displayList();
}

void MainController::stopBookingListProcess()
{
    if (_BLController == nullptr) return;

    delete _BLController;
    _BLController = nullptr;
}
