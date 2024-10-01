#ifndef CLIENTLIST_HPP
#define CLIENTLIST_HPP

#include <QWidget>
#include <QString>
#include <QTableWidgetItem>
#include <QMap>

#include "src/models/Client/Client.hpp"


namespace Ui {
class ClientList;
}

class ClientList : public QWidget
{
    Q_OBJECT

public:
    explicit ClientList(QWidget *parent = nullptr);
    ~ClientList();

    void setClientList(QMap<qint32, Client> cliList);
    void displayList();

private:
    void setTableStyle();
    void enableBookingBtn();
    void enableDeletBtn();
    void disableBookingBtn();
    void disableDeleteBtn();
    void setUserSelectionHandler();
    qint32 getNumListAtRow(qint32 row);

signals:
    void requestBookingFor(Client client);
    void requestDeletionFor(Client client);

private slots:
    void handleBookingSelection(qint32 row);
    void sendBookingRequest();
    void sendDeleteRequest();

private:
    Ui::ClientList *ui;

    Client _client;
    QMap<qint32, Client> _cliList;
};

#endif // CLIENTLIST_HPP
