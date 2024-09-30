QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    src/models/Client \
    src/views/Client

SOURCES += \
    src/controllers/BookingListProcessController/BookingListProcessController.cpp \
    src/controllers/BookingProcessController/ticket.cpp \
    src/controllers/subController.cpp \
    src/main.cpp \
    src/controllers/MainController.cpp \
    src/views/BookingList/BookingListView.cpp \
    src/views/BookingProcess/BookingProcess.cpp \
    src/controllers/BookingProcessController/BookingProcessController.cpp \
    src/views/ClientList/ClientList.cpp \
    src/views/Login/Login.cpp \
    src/views/MainWindow.cpp \
    src/models/Database.cpp \
    src/models/Entity.cpp \
    src/models/Booking/Booking.cpp \
    src/models/Client/Client.cpp \
    src/models/Vehicle/Vehicle.cpp \
    src/views/Booking/BookingView.cpp \
    src/views/Client/ClientView.cpp \
    src/views/VehicleList/VehicleListView.cpp

HEADERS += \
    src/controllers/BookingListProcessController/BookingListProcessController.hpp \
    src/controllers/MainController.hpp \
    src/views/BookingList/BookingListView.hpp \
    src/views/BookingProcess/BookingProcess.hpp \
    src/controllers/BookingProcessController/BookingProcessController.hpp \
    src/views/ClientList/ClientList.hpp \
    src/views/Login/Login.hpp \
    src/views/MainWindow.hpp \
    src/models/Database.hpp \
    src/models/Entity.hpp \
    src/models/Booking/Booking.hpp \
    src/models/Client/Client.hpp \
    src/models/Vehicle/Vehicle.hpp \
    src/views/Booking/BookingView.hpp \
    src/views/Client/ClientView.hpp \
    src/views/VehicleList/VehicleListView.hpp


FORMS += \
    src/views/Booking/BookingView.ui \
    src/views/BookingList/BookingListView.ui \
    src/views/BookingProcess/BookingProcess.ui \
    src/views/Client/ClientView.ui \
    src/views/ClientList/ClientList.ui \
    src/views/Login/Login.ui \
    src/views/MainWindow.ui \
    src/views/VehicleList/VehicleListView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/ressources.qrc
