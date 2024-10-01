#ifndef VEHICLELISTCONTROLLER_HPP
#define VEHICLELISTCONTROLLER_HPP

#include <QObject>

#include "src/views/MainWindow.hpp"
#include "src/views/VehicleList/VehicleListView.hpp"


class VehicleListController : public QObject
{
    Q_OBJECT
public:
    explicit VehicleListController(QObject *parent = nullptr);
    ~VehicleListController();

    void initControllerFor(MainWindow *win);

    void displayList();

private:
    void setDateFilterHandler();

private slots:
    void handleFilterRequest(QDate dateDep);

private:
    MainWindow *_win;
    VehicleListView *_view;

    QMap<qint32, Vehicle> _vehList;
};

#endif // VEHICLELISTCONTROLLER_HPP
