#include "BookingProcessController.hpp"

BookingProcessController::BookingProcessController(QObject *parent)
    : QObject{parent}
    , _BPView(nullptr)
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
    _booking = _BPView->getBooking();
    _booking.setDateRes(QDate::currentDate());
    _booking.syncNumIfNot();

    if (_booking.isValid()) {
        _booking.setFraisTotal(50000);
        return true;
    } else {
        _win->warnUser("Invalid booking data");
        return false;
    }
}


bool BookingProcessController::getClientData()
{
    _client = _BPView->getClient();
    _client.syncNumIfNot();

    if (_client.isValid()) {
        // display the list of vehicle
        //      with the filtered data
        displayVehicleList();
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

    if (!_veh.isValid() ) {
        qDebug() << "Invalid vehicle data";
        return;
    }

    _booking.setNumVeh(_veh.getNum());
    _booking.setNumClient(_client.getNum());

    _veh.decrementFreePlace();

    _booking.addDateDepToDB();
    if (!_client.addToDB()) return;
    if (!_booking.addToDB()) return;
    if (!_veh.upadteDB()) return;

    _win->informUser("Reservation effectuée!");
    changePage(BookingProcess::VEHICLE, BookingProcess::BOOKING);

    createTicket();
}
