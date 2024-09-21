#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

signals:
};

#endif // DATABASE_HPP
