#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _currentPage(WELCOME)
{
    ui->setupUi(this);
    setDefaultConfiguration();
    setPageChangeEventHandler();
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


void MainWindow::setDefaultConfiguration()
{
    ui->mainStack->setCurrentIndex(_currentPage);
}


void MainWindow::setPageChangeEventHandler()
{
    connect(ui->homeBtn, &QPushButton::clicked, [this]() -> void {
        this->handlePageChangeRequest(this->_currentPage, WELCOME);
    });
    connect(ui->bookingBtn, &QPushButton::clicked, [this]() -> void {
        this->handlePageChangeRequest(this->_currentPage, BOOKING);
    });
}


void MainWindow::handlePageChangeRequest(Page from, Page to)
{
    emit requestPageChange(from, to);
}
