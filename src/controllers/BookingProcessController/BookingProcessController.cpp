#include "BookingProcessController.hpp"

BookingProcessController::BookingProcessController(QObject *parent)
    : QObject{parent}
    , _BPView(nullptr)
    , _currentState(State::CREATING)
{}


BookingProcessController::~BookingProcessController()
{
    if (_BPView != nullptr) {
        delete _BPView;
        _BPView = nullptr;
    }
}


void BookingProcessController::initControlFor(MainWindow *win)
{
    if (_BPView == nullptr) {
        _BPView = new BookingProcess();
    }

    _win = win;

    _win->setBookingProcessView(_BPView);
    setConnectionToBP();
}


void BookingProcessController::setBooking(Booking booking)
{
    _BPView->setBooking(booking);
}


void BookingProcessController::setClient(Client client)
{
    _BPView->setClient(client);
}


void BookingProcessController::toCreatingState()
{
    _currentState = State::CREATING;
}


void BookingProcessController::toUpdatingState()
{
    _currentState = State::UPDATING;
}


void BookingProcessController::setConnectionToBP()
{
    if (_BPView == nullptr) return;

    connect(_BPView, &BookingProcess::requestPageChange,
            this, &BookingProcessController::changePage);
    connect(_BPView, &BookingProcess::saveBookingRequest,
            this, &BookingProcessController::saveBooking);
}


bool BookingProcessController::getBookingData()
{
    qint32 num = _booking.getNum();             //  store num if it's for updating
    _booking = _BPView->getBooking();           //  get inputed data
    _booking.setDateRes(QDate::currentDate());  //
    _booking.setFraisTotal(50000);              //
    if (num != 0) _booking.setNum(num);         //  if num are valid then reset it to the booking
    else _booking.syncNumIfNot();               //  else set a new num

    if (_booking.isValid()) {
        return true;
    } else {
        _win->warnUser("Invalid booking data");
        return false;
    }
}


bool BookingProcessController::getClientData()
{
    qint32 num = _client.getNum();              //  store num if it's for updating
    _client = _BPView->getClient();             //  get inputed data
    if (num != 0) _client.setNum(num);          //  if num are valid then reset it to the client
    else _client.syncNumIfNot();                //  else set a new num

    if (_client.isValid()) {
        displayVehicleList();                   // display the list of filtered vehicle
        return true;
    } else {
        _win->warnUser("Invalid client data");
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
        QDate vehDateDep = veh.getDateDep();
        bool validDate = vehDateDep == dateDep;
        validDate = validDate || !vehDateDep.isValid();
        validDate = validDate && veh.getNbPlaceDispo() > 0;

        if (validDate) filteredList[num] = veh;
    }

    _BPView->setVehicleData(filteredList);
}


void BookingProcessController::changePage(
    BookingProcess::Page from,
    BookingProcess::Page to
    )
{
    if (from == to) return;

    switch (to) {
    case BookingProcess::BOOKING :
        _BPView->gotoPage(to);
        // vide
        break;
    case BookingProcess::CLIENT :
        if (getBookingData())
            _BPView->gotoPage(to);
        break;
    case BookingProcess::VEHICLE :
        if (getClientData())
            _BPView->gotoPage(to);
        break;
    }
}


void BookingProcessController::saveBooking()
{
    _veh = _BPView->getVehicle();
    _veh.syncNumIfNot();

    if (!_veh.isValid() )
        return _win->warnUser("Invalid vehicle data");

    if (_currentState == State::UPDATING) {
        qint32 numVeh = _booking.getNumVeh();
        auto list = Vehicle::getList();
        list[numVeh].incrementFreePlace();
        list[numVeh].updateDB();
    }

    _booking.setNumVeh(_veh.getNum());
    _booking.setNumClient(_client.getNum());
    _veh.decrementFreePlace();

    _booking.addDateDepToDB();
    if (_currentState == State::CREATING) {
        if (!_client.addToDB()) return;
        if (!_booking.addToDB()) return;
        if (!_veh.updateDB()) return;
    } else if (_currentState == State::UPDATING) {
        if (!_client.updateDB()) return;
        if (!_booking.updateDB()) return;
        if (!_veh.updateDB()) return;
    }

    _win->informUser("Reservation effectuée!");
    changePage(BookingProcess::VEHICLE, BookingProcess::BOOKING);

    createTicket();
}
