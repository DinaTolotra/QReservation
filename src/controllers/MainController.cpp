#include "MainController.hpp"

MainController::MainController(QObject *parent)
    : QObject{parent}
{
    Database::setupDatabase();
    createWindow();
    setupConnection();
}


MainController::~MainController()
{
    Database::closeDatabase();
}


void MainController::exec()
{
    _win->show();
}


void MainController::createWindow()
{
    _win = new MainWindow();
}


void MainController::setupConnection()
{
    connect(_win, &MainWindow::requestPageChange,
            this, &MainController::changeMainWindowPage);
}

void MainController::changeMainWindowPage(MainWindow::Page from, MainWindow::Page to)
{
    if (to != from) _win->gotoPage(to);
}
