#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _currentPage(WELCOME)
{
    ui->setupUi(this);
    setPageChangeEventHandler();
    gotoPage(_currentPage);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::gotoPage(Page page)
{
    ui->mainStack->setCurrentIndex(page);
    _currentPage = page;
}


void MainWindow::setPageChangeEventHandler()
{
    connect(ui->homeBtn, &QPushButton::clicked,[this]() -> void {
        emit this->requestPageChange(this->_currentPage, WELCOME);
    });
    connect(ui->bookingBtn, &QPushButton::clicked, [this]() -> void {
        emit this->requestPageChange(this->_currentPage, BOOKING);
    });
}
