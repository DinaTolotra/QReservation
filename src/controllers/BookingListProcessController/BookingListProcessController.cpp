#include "BookingListProcessController.hpp"

BookingListProcessController::BookingListProcessController(QObject *parent)
    : QObject{parent}
    , _BLView(nullptr)
{}


BookingListProcessController::~BookingListProcessController()
{
    if (_BLView != nullptr) {
        delete _BLView;
        _BLView = nullptr;
    }
}


void BookingListProcessController::initControlFor(MainWindow *win)
{
    if (_BLView == nullptr) {
        _BLView = new BookingListView();
    }

    _win = win;

    _win->setBookingListView(_BLView);
    handleChangeRequest();
    handleDeleteRequest();
}


void BookingListProcessController::displayList()
{
    auto bookingList = Booking::getList();
    auto clientList = Client::getList();

    _BLView->setBookingList(bookingList);
    _BLView->setClientList(clientList);

    _BLView->displayList();
}


void BookingListProcessController::handleChangeRequest()
{
    connect(_BLView, &BookingListView::requestForModification,
            this, &BookingListProcessController::requestForModification);
}


void BookingListProcessController::handleDeleteRequest()
{
    connect(_BLView, &BookingListView::requestForDeletion,
            this, &BookingListProcessController::processDeletion);
}


void BookingListProcessController::processDeletion(
    Booking booking,
    Client client
    )
{
    bool ok = _win->askUser("Etes-vous sure de supprimer cette réservation?");
    if (!ok) return;

    auto vehList = Vehicle::getList();
    qint32 numVeh = booking.getNumVeh();
    Vehicle veh = vehList[numVeh];
    if (!booking.deleteDB()) return;
    if (!client.deleteDB()) return;
    veh.incrementFreePlace();
    veh.updateDB();
}

