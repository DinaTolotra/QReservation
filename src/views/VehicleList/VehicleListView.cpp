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
    ui->vehicleTable->setRowCount(0);

    int row, col;
    row = col = 0;

    for (Vehicle veh: _vehList) {
        qint32 num = veh.getNum();
        qint32 nbPlace = veh.getNbPlace();
        QDate dateDep = veh.getDateDep();
        qint32 placeDispo = veh.getNbPlaceDispo();
        QString str_dateDep = dateDep.toString("ddd dd/MM");

        if (!dateDep.isValid())
            str_dateDep = "Non spécifier";

        ui->vehicleTable->setRowCount(row+1);

        ui->vehicleTable->setItem(row, col=0, new QTableWidgetItem(QString::number(num)));
        ui->vehicleTable->setItem(row, ++col, new QTableWidgetItem(QString::number(nbPlace)));
        ui->vehicleTable->setItem(row, ++col, new QTableWidgetItem(QString::number(placeDispo)));
        ui->vehicleTable->setItem(row++, ++col, new QTableWidgetItem(str_dateDep));
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
    connect(ui->vehicleTable, &QTableWidget::cellPressed,
            this, &VehicleListView::handleVehicleChoice);
}


void VehicleListView::setSearchRequestHandler()
{
    connect(ui->searchBtn, &QPushButton::clicked,
            this, &VehicleListView::handleSearchRequest);
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


void VehicleListView::handleSearchRequest()
{
    QDate filterDate = ui->dateDepIn->date();

    emit dateDepFilter(filterDate);
}

