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

private:
    Ui::ClientView *ui;
};

#endif // CLIENTVIEW_HPP
