#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCore/QDebug>

#include "src/models/Client/Client.hpp"
#include "src/views/Client/ClientView.hpp"
#include "src/views/BookingProcess/BookingProcess.hpp"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Page {
        WELCOME = 0,
        BOOKING = 1
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void gotoPage(Page page);

    void setBookingProcessView(BookingProcess *BPView);

private:
    void setPageChangeEventHandler();

signals:
    void requestPageChange(MainWindow::Page from, MainWindow::Page to);

private:
    Ui::MainWindow *ui;

    Page _currentPage;

};
#endif // MAINWINDOW_HPP
