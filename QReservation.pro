QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    src/models/Client \
    src/views/Client

SOURCES += \
    src/main.cpp \
    src/models/Client/Client.cpp \
    src/models/Entity.cpp \
    src/views/Client/ClientView.cpp \
    src/views/MainWindow.cpp \
    src/models/Database.cpp

HEADERS += \
    src/models/Client/Client.hpp \
    src/views/Client/ClientView.hpp \
    src/views/MainWindow.hpp \
    src/models/Database.hpp \
    src/models/Entity.hpp


FORMS += \
    src/views/Client/ClientView.ui \
    src/views/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/ressources.qrc
