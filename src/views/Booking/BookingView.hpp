#ifndef BOOKINGVIEW_HPP
#define BOOKINGVIEW_HPP

#include <QGroupBox>

namespace Ui {
class BookingView;
}

class BookingView : public QGroupBox
{
    Q_OBJECT

public:
    explicit BookingView(QWidget *parent = nullptr);
    ~BookingView();

private:
    Ui::BookingView *ui;
};

#endif // BOOKINGVIEW_HPP
