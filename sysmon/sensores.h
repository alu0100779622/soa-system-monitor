#ifndef SENSORES_H
#define SENSORES_H

#include "data_sensores.h"
#include <QThread>
#include <QDir>
#include <QVector>


class sensores : public QThread
{
    Q_OBJECT
private:
    data_sensores *buffer;
public:
    explicit sensores(data_sensores *cont, QObject *parent = 0);
    int get_buffer_size(void);
public slots:
    void run (void);
signals:
    void refreshInfo(int);
};

#endif // SENSORES_H
