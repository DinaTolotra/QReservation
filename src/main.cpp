#include <QApplication>
#include "views/MainWindow.hpp"
#include "models/Database.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    win.show();
    Database::setupDatabase();
    a.exec();
    Database::closeDatabase();
    return 0;
}
