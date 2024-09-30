#include "Login.hpp"
#include "ui_Login.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setLoginHandler();
    setPasswordDisplay();
}

Login::~Login()
{
    delete ui;
}


void Login::closeEvent(QCloseEvent *event)
{
    if (askUserOnExiting()) {
        event->accept();
        reject();
    } else {
        event->ignore();
    }
}


bool Login::getData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "loginConn");
    db.setDatabaseName("LOGIN");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
    if (!ok) {
        qDebug() << db.lastError();
        return false;
    }

    QSqlQuery query(db);
    query.exec("SELECT * FROM USER");

    while (query.next()) {
        QString username = query.value("USERNAME").toString();
        QString password = query.value("PASSWORD").toString();
        _loginData.insert(username, password);
    }

    query.clear();

    db.close();
    QSqlDatabase::removeDatabase("loginConn");

    return !_loginData.isEmpty();
}


void Login::setLoginHandler()
{
    connect(ui->loginBtn, &QPushButton::clicked,
            this, &Login::handleLoginRequest);
    connect(ui->cancelBtn, &QPushButton::clicked,
            this, &Login::handleExitRequest);
}


void Login::setPasswordDisplay()
{
    ui->passwordIn->setEchoMode(QLineEdit::Password);
}


bool Login::checkLoginData(
    QString username,
    QString password)
{
    getData();

    bool usernameExist = _loginData.contains(username);
    if (!usernameExist) return false;
    return _loginData[username] == password;
}


bool Login::askUserOnExiting()
{
    auto reponse = QMessageBox::critical(
        this, "Quoi!?", "Etes-vous sure de vouloir quitter l'application?",
        QMessageBox::Yes, QMessageBox::No);

    if (reponse == QMessageBox::Yes)
        return true;
    return false;
}


void Login::warnUserOnWrongLogin()
{
    QMessageBox::warning(
        this, "Invalide",
        "Les données saisie sont invalide!"
        );
}


void Login::handleExitRequest()
{
    if (askUserOnExiting())
        reject();
}


void Login::handleLoginRequest()
{
    QString username = ui->usernameIn->text();
    QString password = ui->passwordIn->text();

    bool valid = checkLoginData(username, password);
    if (valid) accept();
    else warnUserOnWrongLogin();
}
