#ifndef VEHICLELISTVIEW_HPP
#define VEHICLELISTVIEW_HPP

#include <QGroupBox>

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
    Ui::VehicleListView *ui;
};

#endif // VEHICLELISTVIEW_HPP
