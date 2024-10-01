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

    _BLController = new BookingListController();
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


void MainController::initClientList()
{
    if (_win == nullptr) return;
    if (_clientListController != nullptr) return;

    _clientListController = new ClientListController();
    _clientListController->initControllerFor(_win);
    _clientListController->displayList();
    setClientModifHandler();
}


void MainController::stopClientList()
{
    if (_clientListController == nullptr) return;

    delete _clientListController;
    _clientListController = nullptr;
}


void MainController::initVehicleList()
{
    if (_win == nullptr) return;
    if (_vehListController != nullptr) return;

    _vehListController = new VehicleListController();
    _vehListController->initControllerFor(_win);
    _vehListController->displayList();
}


void MainController::stopVehicleList()
{
    if (_vehListController == nullptr) return;

    delete _vehListController;
    _vehListController = nullptr;
}


void MainController::setBookingModifHandler()
{
    connect(
        _BLController, &BookingListController::requestModifFor,
        this, &MainController::performModif
        );
}


void MainController::setClientModifHandler()
{
    connect(
        _clientListController, &ClientListController::requestBookingFor,
        this, &MainController::performBooking
        );
}
