#include "VehicleListView.hpp"
#include "ui_VehicleListView.h"

VehicleListView::VehicleListView(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::VehicleListView)
{
    ui->setupUi(this);
    setUserChoiceHandler();
}

VehicleListView::~VehicleListView()
{
    delete ui;
}


void VehicleListView::setVehicleList(QMap<qint32, Vehicle> vehicleList)
{
    _vehList = vehicleList;
}


void VehicleListView::displayList()
{
    int row, col;
    row = col = 0;

    for (Vehicle veh: _vehList) {
        qint32 num = veh.getNum();
        qint32 nbPlace = veh.getNbPlace();
        qint32 nbPlaceDispo = veh.getNbPlaceDispo();

        ui->vehicleTable->setRowCount(row+1);

        QTableWidgetItem *numItem = new QTableWidgetItem(QString::number(num));
        QTableWidgetItem *nbPlaceItem = new QTableWidgetItem(QString::number(nbPlace));
        QTableWidgetItem *nbPlaceDispoItem = new QTableWidgetItem(QString::number(nbPlaceDispo));

        ui->vehicleTable->setItem(row, col=0, numItem);
        ui->vehicleTable->setItem(row, ++col, nbPlaceItem);
        ui->vehicleTable->setItem(row++, ++col, nbPlaceDispoItem);
    }
}


Vehicle VehicleListView::getVehicle()
{
    return _veh;
}


void VehicleListView::setUserChoiceHandler()
{
    connect(ui->vehicleTable, &QTableWidget::cellDoubleClicked,
            this, &VehicleListView::handleVehicleChoice);
}


qint32 VehicleListView::getVehicleNumInRow(qint32 row)
{
    QTableWidgetItem *cellWgt = ui->vehicleTable->item(row, 0);
    return cellWgt->text().toInt();
}


void VehicleListView::handleVehicleChoice(qint32 row)
{
    qint32 numVeh = getVehicleNumInRow(row);
    if (!_vehList.contains(numVeh)) return;
    Vehicle veh =_vehList[numVeh];
    emit vehicleChoosed(veh);
    displayChoice(veh);
    _veh = veh;
}


void VehicleListView::displayChoice(Vehicle veh)
{
    qint32 num = veh.getNum();
    qint32 nbPlace = veh.getNbPlace();
    qint32 nbPlaceDispo = veh.getNbPlaceDispo();
    QString imgPath = ":/images/images/bus_?_64.png";

    imgPath.replace("?", QString::number(num % 2));

    ui->vehImg->setPixmap(QPixmap(imgPath));
    ui->vehNumDisp->display(num);
    ui->placeDisp->display(nbPlace);
    ui->freePlaceDisp->display(nbPlaceDispo);
}
