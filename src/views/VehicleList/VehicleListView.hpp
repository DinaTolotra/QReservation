#ifndef VEHICLELISTVIEW_HPP
#define VEHICLELISTVIEW_HPP

#include <QGroupBox>
#include <QLabel>
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

private:
    void setUserChoiceHandler();

    qint32 getRowVehicleNum(qint32 row);

signals:
    void vehicleChoosed(Vehicle veh);

private slots:
    void handleVehicleChoice(qint32 row, qint32 col);

private:
    Ui::VehicleListView *ui;
    QMap<qint32, Vehicle> vehicleList;
};

#endif // VEHICLELISTVIEW_HPP
