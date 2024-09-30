#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QMessageBox>
#include <QCloseEvent>
#include <QDialog>
#include <QDebug>
#include <QMap>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void closeEvent(QCloseEvent *event);

private:
    bool getData();
    void setLoginHandler();
    void setPasswordDisplay();
    bool checkLoginData(
        QString username,
        QString password
        );

    bool askUserOnExiting();
    void warnUserOnWrongLogin();

private slots:
    void handleExitRequest();
    void handleLoginRequest();

private:
    Ui::Login *ui;
    QMap<QString, QString> _loginData;
};

#endif // LOGIN_HPP
