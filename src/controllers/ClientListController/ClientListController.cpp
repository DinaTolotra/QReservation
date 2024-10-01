#include "ClientListController.hpp"

ClientListController::ClientListController(QObject *parent)
    : QObject{parent}
    , _win(nullptr)
    , _clientListView(nullptr)
{}


ClientListController::~ClientListController()
{
    if (_clientListView != nullptr) {
        delete _clientListView;
        _clientListView = nullptr;
    }
}


void ClientListController::initControllerFor(MainWindow *win)
{
    _win = win;
    if (_clientListView == nullptr) {
        _clientListView = new ClientList(_win);
    }

    _win->setClientListView(_clientListView);
    setConnectionToView();
}


void ClientListController::displayList()
{
    auto clientList = Client::getList();

    _clientListView->setClientList(clientList);
    _clientListView->displayList();
}


void ClientListController::setConnectionToView()
{
    connect(_clientListView, &ClientList::requestBookingFor,
            this, &ClientListController::requestBookingFor);
    connect(_clientListView, &ClientList::requestDeletionFor,
            this, &ClientListController::deleteClient);
}

void ClientListController::deleteClient(Client client)
{
    bool ok = _win->askUser("Etes-vous sure de supprimer cette client?");

    if (!ok) return;
    if (!client.deleteDB()) return;
}
