#include "VehicleListController.hpp"

VehicleListController::VehicleListController(QObject *parent)
    : QObject{parent}
    , _win(nullptr)
    , _view(nullptr)
{}


VehicleListController::~VehicleListController()
{
    if (_view != nullptr) {
        delete _view;
        _view = nullptr;
    }
}


void VehicleListController::initControllerFor(MainWindow *win)
{
    _win = win;

    if (_view == nullptr) {
        _view = new VehicleListView(_win);
    }

    _win->setVehicleListView(_view);
    setFilterRequestHandler();
}


void VehicleListController::displayList()
{
    auto vehList = Vehicle::getList();

    _view->setVehicleList(vehList);
    _view->displayList();
}


void VehicleListController::setFilterRequestHandler()
{
    connect(_view, &VehicleListView::dateDepFilter,
            this, &VehicleListController::handleFilterRequest);
}


void VehicleListController::handleFilterRequest(QDate dateDep)
{
    QMap<qint32, Vehicle> list = Vehicle::getList();
    QMap<qint32, Vehicle> filteredList;

    for (Vehicle veh: list) {
        qint32 num = veh.getNum();
        QDate vehDateDep = veh.getDateDep();
        bool validDate = vehDateDep == dateDep;
        validDate = validDate || !vehDateDep.isValid();

        if (validDate) filteredList[num] = veh;
    }

    _view->setVehicleList(filteredList);
    _view->displayList();
    setFilterRequestHandler();
}
