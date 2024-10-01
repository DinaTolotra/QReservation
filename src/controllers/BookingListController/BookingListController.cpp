#include "BookingListController.hpp"

BookingListController::BookingListController(QObject *parent)
    : QObject{parent}
    , _view(nullptr)
{}


BookingListController::~BookingListController()
{
    if (_view != nullptr) {
        delete _view;
        _view = nullptr;
    }
}


void BookingListController::initControlFor(MainWindow *win)
{
    _win = win;

    if (_view == nullptr) {
        _view = new BookingListView(_win);
    }

    _win->setBookingListView(_view);
    setChangeRequestHandler();
    setDeleteRequestHandler();
    setFilterRequestHandler();
}


void BookingListController::displayList()
{
    auto bookingList = Booking::getList();
    auto clientList = Client::getList();

    _view->setBookingList(bookingList);
    _view->setClientList(clientList);

    _view->displayList();
}


void BookingListController::setChangeRequestHandler()
{
    connect(_view, &BookingListView::requestModificationFor,
            this, &BookingListController::requestModifFor);
}


void BookingListController::setDeleteRequestHandler()
{
    connect(_view, &BookingListView::requestDeletionFor,
            this, &BookingListController::processDeletion);
}


void BookingListController::setFilterRequestHandler()
{
    connect(_view, &BookingListView::requestCliNameFilter,
            this, &BookingListController::handleFilterRequest);
}


void BookingListController::processDeletion(
    Booking booking,
    Client client
    )
{
    bool ok = _win->askUser(
        "Supprimer cette réservation?"
        );

    if (!ok) return;

    if (!booking.deleteDB()) return;
    if (!client.deleteDB()) return;
}


void BookingListController::handleFilterRequest(QString name)
{
    if (name.isEmpty()) {
        displayList();
        return;
    }

    QMap<qint32, Booking> bookingList = Booking::getList();
    QMap<qint32, Client> clientList = Client::getList();
    QMap<qint32, Booking> filteredData;
    name = name.toLower();

    for (Booking booking: bookingList) {
        qint32 bookingNum = booking.getNum();
        qint32 cliNum = booking.getcliNum();
        Client cli = clientList[cliNum];
        QString cliName = cli.getNom();
        cliName = cliName.toLower();

        if (cliName.contains(name))
            filteredData.insert(
                bookingNum,
                booking
                );
    }

    _view->setBookingList(filteredData);
    _view->setClientList(clientList);

    _view->displayList();
}
