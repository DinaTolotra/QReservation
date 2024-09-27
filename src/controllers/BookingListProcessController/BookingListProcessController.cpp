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
}


void BookingListProcessController::displayList()
{
    auto bookingList = Booking::getList();
    auto clientList = Client::getList();

    _BLView->setBookingList(bookingList);
    _BLView->setClientList(clientList);

    _BLView->displayList();
}
