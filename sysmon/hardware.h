#ifndef HARDWARE_H
#define HARDWARE_H

#include "QObject"
#include "QProcess"

class hardware : public QObject
{
   Q_OBJECT
private:
     QByteArray datoslshw;
public slots :
    void lshw();
    QByteArray transferenciadatos();
signals:
    void ejecute(int);


};

#endif // HARDWARE_H
