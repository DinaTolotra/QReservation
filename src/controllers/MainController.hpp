#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <QObject>
#include <QString>
#include <stdexcept>

#include "src/models/Database.hpp"
#include "src/views/MainWindow.hpp"
#include "BookingProcessController/BookingProcessController.hpp"
#include "BookingListProcessController/BookingListProcessController.hpp"


class MainController : public QObject
{
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

    void exec();

private:
    bool createWindow();
    void setupConnection();

    void initBookingProcess();
    void stopBookingProcess();
    void initBookingListProcess();
    void stopBookingListProcess();

private slots:
    void changePage(MainWindow::Page from, MainWindow::Page to);

private:
    MainWindow *_win;

    BookingProcessController *_BPController;
    BookingListProcessController *_BLController;

};

#endif // MAINCONTROLLER_HPP
