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


void VehicleListView::setUserChoiceHandler()
{
    connect(ui->vehicleTable, &QTableWidget::cellDoubleClicked,
            this, &VehicleListView::handleVehicleChoice);
}


qint32 VehicleListView::getRowVehicleNum(qint32 row)
{
    QTableWidgetItem *cellWgt = ui->vehicleTable->itemAt(0, row);
    return cellWgt->text().toInt();
}


void VehicleListView::handleVehicleChoice(qint32 row)
{
    qint32 numveh = getRowVehicleNum(row);
    if (!_vehList.contains(numveh)) return;
    emit vehicleChoosed(_vehList[numveh]);
}
