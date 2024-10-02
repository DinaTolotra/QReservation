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
    connect(_view, &BookingListView::requestFilter,
            this, &BookingListController::handleFilterRequest);
}


void BookingListController::processDeletion(Booking booking)
{
    bool ok = _win->askUser(
        "Supprimer cette réservation?"
        );

    if (!ok) return;

    if (!booking.deleteDB()) return;
    displayList();
}


void BookingListController::handleFilterRequest(QString filter)
{
    if (filter.isEmpty()) {
        displayList();
        return;
    }

    QMap<qint32, Booking> bookingList = Booking::getList();
    QMap<qint32, Client> clientList = Client::getList();
    QMap<qint32, Booking> filteredData;
    filter = filter.toLower();

    for (Booking booking: bookingList) {
        qint32 bookingNum = booking.getNum();
        QDate dateDep = booking.getDateDep();
        qint32 cliNum = booking.getcliNum();
        Client cli = clientList[cliNum];
        QString cliName = cli.getNom();

        QString str_dateDep = dateDep.toString("dd/MM");
        QString str_num = QString::number(bookingNum);
        cliName = cliName.toLower();

        QRegularExpression dateFormat("\\d\\d/\\d\\d");

        bool ok = filter.contains(dateFormat)
                  && str_dateDep.contains(filter);
        ok = ok || cliName.contains(filter);
        ok = ok || str_num.contains(filter);

        if (ok) filteredData.insert(
                bookingNum,booking
                );
    }

    _view->setBookingList(filteredData);
    _view->setClientList(clientList);

    _view->displayList();
}
