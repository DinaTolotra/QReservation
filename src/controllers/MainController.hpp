#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <QObject>
#include <QString>

#include "src/models/Database.hpp"
#include "src/views/MainWindow.hpp"


class MainController : public QObject
{
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

    void exec();

private:
    void createWindow();
    void setupConnection();

private slots:
    void changeMainWindowPage(MainWindow::Page from, MainWindow::Page to);
    void changeBookingProcessPage();

private:
    MainWindow *_win;

};

#endif // MAINCONTROLLER_HPP
