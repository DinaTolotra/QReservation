#include <QApplication>
#include "src/views/Login/Login.hpp"
#include "src/controllers/MainController.hpp"


bool loginUser();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (loginUser()) {
        MainController engine;
        engine.exec();
        a.exec();
    }

    return 0;
}


bool loginUser()
{
    Login login;
    int retCode = login.exec();
    return retCode == QDialog::Accepted;
}
