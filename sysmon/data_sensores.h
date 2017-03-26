#ifndef DATA_SENSORES_H
#define DATA_SENSORES_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <QPair>

class data_sensores  : public QObject{
private:
    QVector<QPair<QString, QString>> info;
    QMutex mutex;
    int counter;
public:
    data_sensores();
    ~data_sensores();
    int get_counter();
    void insert_info(const QPair<QString,QString> &pair);
    QPair<QString,QString> extract_info();
};

#endif // DATA_SENSORES_H
