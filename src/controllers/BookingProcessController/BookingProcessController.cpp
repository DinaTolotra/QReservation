#include "BookingProcessController.hpp"

BookingProcessController::BookingProcessController(QObject *parent)
    : QObject{parent}
    , _view(nullptr)
    , _currentState(State::CREATING)
{}


BookingProcessController::~BookingProcessController()
{
    if (_view != nullptr) {
        delete _view;
        _view = nullptr;
    }
}


void BookingProcessController::initControlFor(MainWindow *win)
{
    if (_view == nullptr) {
        _view = new BookingProcess();
    }

    _win = win;

    _win->setBookingProcessView(_view);
    setConnectionToBP();
}


void BookingProcessController::setBooking(Booking booking)
{
    _view->setBooking(booking);
    _booking = booking;
}


void BookingProcessController::setClient(Client client)
{
    _view->setClient(client);
    _client = client;
}


void BookingProcessController::toCreatingState()
{
    _currentState = State::CREATING;
}


void BookingProcessController::toUpdatingState()
{
    _currentState = State::UPDATING;
}


void BookingProcessController::toAddingState()
{
    _currentState = State::ADDING;
}


void BookingProcessController::setConnectionToBP()
{
    if (_view == nullptr) return;

    connect(_view, &BookingProcess::requestPageChange,
            this, &BookingProcessController::changePage);
    connect(_view, &BookingProcess::saveBookingRequest,
            this, &BookingProcessController::saveBooking);
}


bool BookingProcessController::getBookingData()
{
    qint32 num = _booking.getNum();

    _booking = _view->getBooking();
    _booking.setFraisTotal(50000);
    _booking.setDateRes(QDate::currentDate());

    if (_currentState == UPDATING)
        _booking.setNum(num);
    else _booking.syncNum();

    if (_booking.isValid()) {
        return true;
    } else {
        _win->warnUser(
            "Invalid booking data"
            );
        return false;
    }
}


bool BookingProcessController::getClientData()
{
    qint32 num = _client.getNum();
    _client = _view->getClient();

    if (_currentState == CREATING)
        _client.syncNum();
    else if (num != 0)
        _client.setNum(num);

    if (_client.isValid()) {
        displayVehicleList();
        return true;
    } else {
        _win->warnUser(
            "Invalid client data"
            );
        return false;
    }
}


bool BookingProcessController::getVehicleData()
{
    _veh = _view->getVehicle();

    if (_veh.isValid()) {
        return true;
    } else {
        _win->warnUser(
            "Invalid vehicle data"
            );
        return false;
    }
}


void BookingProcessController::displayVehicleList()
{
    QMap<qint32, Vehicle> list = Vehicle::getList();
    QMap<qint32, Vehicle> filteredList;
    QDate dateDep = _booking.getDateDep();

    for (Vehicle veh: list) {
        qint32 num = veh.getNum();

        if (isVehicleValidFor(veh, dateDep))
            filteredList[num] = veh;
    }

    _view->setVehicleData(filteredList);
}


bool BookingProcessController::isVehicleValidFor(
    Vehicle veh,
    QDate dateDep
    )
{
    QDate vehDateDep = veh.getDateDep();
    return vehDateDep == dateDep || !vehDateDep.isValid();
}


void BookingProcessController::changePage(
    BookingProcess::Page from,
    BookingProcess::Page to
    )
{
    switch (from) {
    case BookingProcess::BOOKING :
        if (!getBookingData())
            return;
        break;
    case BookingProcess::CLIENT :
        if (!getClientData())
            return;
        break;
    case BookingProcess::VEHICLE :
        break;
    }

    _view->gotoPage(to);
}


void BookingProcessController::saveBooking()
{
    if (!getVehicleData()) return;

    _booking.setNumVeh(_veh.getNum());
    _booking.setcliNum(_client.getNum());

    _booking.addDateDepToDB();

    switch (_currentState) {
    case State::CREATING:
        if (!_client.addToDB()) return;
        if (!_booking.addToDB()) return;
        break;
    case State::UPDATING:
        if (!_client.updateDB()) return;
        if (!_booking.updateDB()) return;
        break;
    case State::ADDING:
        if (!_client.updateDB()) return;
        if (!_booking.addToDB()) return;
        break;
    }

    _win->informUser("Reservation effectuée!");
    changePage(BookingProcess::VEHICLE,
               BookingProcess::BOOKING
               );
}
