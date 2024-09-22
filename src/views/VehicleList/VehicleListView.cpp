#include "VehicleListView.hpp"
#include "ui_VehicleListView.h"

VehicleListView::VehicleListView(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::VehicleListView)
{
    ui->setupUi(this);
}

VehicleListView::~VehicleListView()
{
    delete ui;
}
