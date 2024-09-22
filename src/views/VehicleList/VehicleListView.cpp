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


void VehicleListView::handleVehicleChoice(qint32 row, qint32 col)
{
    qint32 numveh = getRowVehicleNum(row);
    if (!vehicleList.contains(numveh)) return;
    emit vehicleChoosed(vehicleList[numveh]);
}
