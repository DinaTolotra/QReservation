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
    connect(_view, &ClientList::requestFilter,
            this, &ClientListController::handleFilterRequest);
}


void ClientListController::deleteClient(Client client)
{
    bool ok = _win->askUser("Supprimer cette client?");

    if (!ok) return;
    if (!client.deleteDB()) return;
    displayList();
}


void ClientListController::handleFilterRequest(QString filter)
{
    if (filter.isEmpty()) {
        displayList();
        return;
    }

    QMap<qint32, Client> clientList = Client::getList();
    QMap<qint32, Client> filteredData;
    filter = filter.toLower();

    for (Client cli: clientList) {
        qint32 cliNum = cli.getNum();
        QString cliName = cli.getNom();
        QString cliTel = cli.getTelephone();
        QString str_num = QString::number(cliNum);

        cliName = cliName.toLower();

        bool ok = filter.contains("+261")
                  && cliTel.contains(filter);
        ok = ok || cliName.contains(filter);
        ok = ok || str_num.contains(filter);

        if (ok) filteredData.insert(
                cliNum, cli
                );
    }

    _view->setClientList(filteredData);
    _view->displayList();
}
