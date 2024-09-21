#include <QApplication>
#include "views/MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    win.show();
    return a.exec();
}
