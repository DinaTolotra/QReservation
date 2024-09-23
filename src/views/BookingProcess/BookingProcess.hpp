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
    enum Page {
        BOOKING = 0,
        CLIENT = 1,
        VEHICLE = 2
    };

public:
    explicit BookingProcess(QWidget *parent = nullptr);
    ~BookingProcess();

    void gotoPage(Page page);

private:
    void setPageChangeEventHandler();

signals:
    void requestPageChange(Page from, Page to);
    void saveBookingRequest();

private:
    Ui::BookingProcess *ui;
    Page _currentPage;
};

#endif // BOOKINGPROCESS_HPP
