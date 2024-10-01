#include "VehicleListView.hpp"
#include "ui_VehicleListView.h"

VehicleListView::VehicleListView(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::VehicleListView)
{
    ui->setupUi(this);
    setTableStyle();
    setCurrentDate();
    setUserChoiceHandler();
    setSearchRequestHandler();
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
    ui->vehicleTable->clearContents();

    int row, col;
    row = col = 0;

    for (Vehicle veh: _vehList) {
        qint32 num = veh.getNum();
        qint32 nbPlace = veh.getNbPlace();
        qint32 placeDispo = veh.getNbPlaceDispo();

        ui->vehicleTable->setRowCount(row+1);

        QTableWidgetItem *numItem = new QTableWidgetItem(QString::number(num));
        QTableWidgetItem *nbPlaceItem = new QTableWidgetItem(QString::number(nbPlace));
        QTableWidgetItem *placeDispoItem = new QTableWidgetItem(QString::number(placeDispo));

        ui->vehicleTable->setItem(row, col=0, numItem);
        ui->vehicleTable->setItem(row, ++col, nbPlaceItem);
        ui->vehicleTable->setItem(row++, ++col, placeDispoItem);
    }
}


Vehicle VehicleListView::getVehicle()
{
    return _veh;
}


void VehicleListView::disableSearch()
{
    ui->searchBtn->setEnabled(false);
    ui->dateDepIn->setEnabled(false);
}


void VehicleListView::setTableStyle()
{
    auto *headerView = ui->vehicleTable->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
}


void VehicleListView::setCurrentDate()
{
    ui->dateDepIn->setDate(QDate::currentDate());
}


void VehicleListView::setUserChoiceHandler()
{
    connect(ui->vehicleTable, &QTableWidget::cellDoubleClicked,
            this, &VehicleListView::handleVehicleChoice);
}


void VehicleListView::setSearchRequestHandler()
{
    connect(ui->searchBtn, &QPushButton::clicked,
            this, &VehicleListView::handlesearchRequest);
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
    QVector<QString> busImgPath = {
        ":/images/images/bus_green.png",
        ":/images/images/bus_white.png",
        ":/images/images/bus_red.png"
    };

    qint32 num = veh.getNum();
    qint32 nbPlace = veh.getNbPlace();
    qint32 nbPlaceDispo = veh.getNbPlaceDispo();

    ui->vehImg->setPixmap(QPixmap(busImgPath[num%3]));
    ui->vehNumDisp->display(num);
    ui->placeDisp->display(nbPlace);
    ui->freePlaceDisp->display(nbPlaceDispo);
}


void VehicleListView::handlesearchRequest()
{
    QDate filterDate = ui->dateDepIn->date();

    emit dateDepFilter(filterDate);
}

