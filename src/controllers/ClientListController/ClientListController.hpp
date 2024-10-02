#ifndef CLIENTLISTCONTROLLER_HPP
#define CLIENTLISTCONTROLLER_HPP

#include <QObject>

#include "src/views/MainWindow.hpp"
#include "src/views/ClientList/ClientList.hpp"


class ClientListController : public QObject
{
    Q_OBJECT
public:
    explicit ClientListController(QObject *parent = nullptr);
    ~ClientListController();

    void initControllerFor(MainWindow *win);
    void displayList();

private:
    void setConnectionToView();
    void setNameFilterHandler();

private slots:
    void deleteClient(Client client);
    void handleFilterRequest(QString filter);

signals:
    void requestBookingFor(Client client);

private:
    MainWindow *_win;
    ClientList *_view;
};

#endif // CLIENTLISTCONTROLLER_HPP
