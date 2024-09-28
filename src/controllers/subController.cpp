#include "MainController.hpp"


void MainController::initBookingProcess()
{
    if (_win == nullptr) return;
    if (_BPController != nullptr) return;

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
    if (_win == nullptr) return;
    if (_BLController != nullptr) return;

    _BLController = new BookingListProcessController();
    _BLController->initControlFor(_win);
    _BLController->displayList();
    setBookingModifHandler();
}

void MainController::stopBookingListProcess()
{
    if (_BLController == nullptr) return;

    delete _BLController;
    _BLController = nullptr;
}


void MainController::setBookingModifHandler()
{
    connect(_BLController, &BookingListProcessController::requestForModification,
            this, &MainController::performModif);
}
