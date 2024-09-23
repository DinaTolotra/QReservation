#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCore/QDebug>

#include "Client.hpp"
#include "ClientView.hpp"


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

private:
    void setDefaultConfiguration();
    void setPageChangeEventHandler();

signals:
    void requestPageChange(Page from, Page to);

private slots:
    void handlePageChangeRequest(Page from, Page to);

private:
    Ui::MainWindow *ui;

    Page _currentPage;

};
#endif // MAINWINDOW_HPP
