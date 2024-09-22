#ifndef VEHICLELISTVIEW_HPP
#define VEHICLELISTVIEW_HPP

#include <QGroupBox>
#include <QLabel>
#include <QPair>
#include <QMap>

#include "src/models/Vehicle/Vehicle.hpp"


namespace Ui {
class VehicleListView;
}

class VehicleListView : public QGroupBox
{
    Q_OBJECT

public:
    explicit VehicleListView(QWidget *parent = nullptr);
    ~VehicleListView();

    void setVehicleList(QMap<qint32, Vehicle> vehicleList);

    void displayList();

private:
    void setUserChoiceHandler();

    qint32 getVehicleNumInRow(qint32 row);

signals:
    void vehicleChoosed(Vehicle veh);

private slots:
    void handleVehicleChoice(qint32 row);
    void displayChoice(Vehicle veh);

private:
    Ui::VehicleListView *ui;
    QMap<qint32, Vehicle> _vehList;
};

#endif // VEHICLELISTVIEW_HPP
