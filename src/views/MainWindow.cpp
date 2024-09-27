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


void MainWindow::setBookingProcessView(BookingProcess *BPView)
{
    auto *BPLyt = ui->BPContainer->layout();
    BPLyt->addWidget(BPView);
}


void MainWindow::setBookingListView(BookingListView *BLView)
{
    auto BLLyt = ui->bookingListPage->layout();
    BLLyt->addWidget(BLView);
}


void MainWindow::warnUser(QString message)
{
    QMessageBox::warning(this, "Warning", message);
}


void MainWindow::informUser(QString message)
{
    QMessageBox::information(this, "Info", message);
}


void MainWindow::setPageChangeEventHandler()
{
    connect(ui->homeBtn, &QPushButton::clicked, [this]() -> void {
        emit this->requestPageChange(this->_currentPage, WELCOME);
    });
    connect(ui->bookingBtn, &QPushButton::clicked, [this]() -> void {
        emit this->requestPageChange(this->_currentPage, BOOKING);
    });
    connect(ui->listBtn, &QPushButton::clicked, [this]() -> void {
        emit this->requestPageChange(this->_currentPage, LIST);
    });
}
