#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup database
    _db = new Database();
    _db->setupConnection();
    _db->setupQuery();
}

MainWindow::~MainWindow()
{
    _db->disconnect();

    delete _db;
    delete ui;
}
