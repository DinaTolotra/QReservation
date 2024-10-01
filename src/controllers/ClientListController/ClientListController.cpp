#include "ClientListController.hpp"

ClientListController::ClientListController(QObject *parent)
    : QObject{parent}
    , _win(nullptr)
    , _view(nullptr)
{}


ClientListController::~ClientListController()
{
    if (_view != nullptr) {
        delete _view;
        _view = nullptr;
    }
}


void ClientListController::initControllerFor(MainWindow *win)
{
    _win = win;
    if (_view == nullptr) {
        _view = new ClientList(_win);
    }

    _win->setClientListView(_view);
    setConnectionToView();
    setNameFilterHandler();
}


void ClientListController::displayList()
{
    auto clientList = Client::getList();

    _view->setClientList(clientList);
    _view->displayList();
}


void ClientListController::setConnectionToView()
{
    connect(_view, &ClientList::requestBookingFor,
            this, &ClientListController::requestBookingFor);
    connect(_view, &ClientList::requestDeletionFor,
            this, &ClientListController::deleteClient);
}


void ClientListController::setNameFilterHandler()
{
    connect(_view, &ClientList::requestNameFilter,
            this, &ClientListController::handleFilterRequest);
}


void ClientListController::deleteClient(Client client)
{
    bool ok = _win->askUser("Etes-vous sure de supprimer cette client?");

    if (!ok) return;
    if (!client.deleteDB()) return;
}


void ClientListController::handleFilterRequest(QString name)
{
    if (name.isEmpty()) {
        displayList();
        return;
    }

    QMap<qint32, Client> clientList = Client::getList();
    QMap<qint32, Client> filteredData;
    name = name.toLower();

    for (Client cli: clientList) {
        QString cliName = cli.getNom();
        qint32 cliNum = cli.getNum();
        cliName = cliName.toLower();

        if (cliName.contains(name))
            filteredData.insert(cliNum, cli);
    }

    _view->setClientList(filteredData);
    _view->displayList();
}
