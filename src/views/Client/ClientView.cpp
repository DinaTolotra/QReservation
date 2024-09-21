#include "ClientView.hpp"
#include "ui_ClientView.h"

ClientView::ClientView(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ClientView)
{
    ui->setupUi(this);
}

ClientView::~ClientView()
{
    delete ui;
}
