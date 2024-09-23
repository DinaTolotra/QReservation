#ifndef BOOKINGPROCESS_HPP
#define BOOKINGPROCESS_HPP

#include <QStackedWidget>

namespace Ui {
class BookingProcess;
}

class BookingProcess : public QStackedWidget
{
    Q_OBJECT

public:
    explicit BookingProcess(QWidget *parent = nullptr);
    ~BookingProcess();

private:
    Ui::BookingProcess *ui;
};

#endif // BOOKINGPROCESS_HPP
