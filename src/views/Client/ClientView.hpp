#ifndef CLIENTVIEW_HPP
#define CLIENTVIEW_HPP

#include <QGroupBox>

#include "Client.hpp"


namespace Ui {
class ClientView;
}

class ClientView : public QGroupBox
{
    Q_OBJECT

public:
    explicit ClientView(QWidget *parent = nullptr);
    ~ClientView();

    Client getClient();

private:
    static QString formatTelToMada(QString incompletTel);

private:
    Client _client;
    Ui::ClientView *ui;
};

#endif // CLIENTVIEW_HPP
