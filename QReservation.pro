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
    src/models/Booking/Booking.cpp \
    src/models/Client/Client.cpp \
    src/models/Entity.cpp \
    src/models/Vehicle/Vehicle.cpp \
    src/views/Booking/BookingView.cpp \
    src/views/Client/ClientView.cpp \
    src/views/MainWindow.cpp \
    src/models/Database.cpp \
    src/views/VehicleList/VehicleListView.cpp

HEADERS += \
    src/models/Booking/Booking.hpp \
    src/models/Client/Client.hpp \
    src/models/Vehicle/Vehicle.hpp \
    src/views/Booking/BookingView.hpp \
    src/views/Client/ClientView.hpp \
    src/views/MainWindow.hpp \
    src/models/Database.hpp \
    src/models/Entity.hpp \
    src/views/VehicleList/VehicleListView.hpp


FORMS += \
    src/views/Booking/BookingView.ui \
    src/views/Client/ClientView.ui \
    src/views/MainWindow.ui \
    src/views/VehicleList/VehicleListView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/ressources.qrc
