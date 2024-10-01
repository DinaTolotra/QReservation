#include <QApplication>
#include "src/controllers/MainController.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController engine;
    engine.exec();
    a.exec();

    return 0;
}
