#ifndef CLIENTLIST_HPP
#define CLIENTLIST_HPP

#include <QWidget>

namespace Ui {
class ClientList;
}

class ClientList : public QWidget
{
    Q_OBJECT

public:
    explicit ClientList(QWidget *parent = nullptr);
    ~ClientList();

private:
    Ui::ClientList *ui;
};

#endif // CLIENTLIST_HPP
