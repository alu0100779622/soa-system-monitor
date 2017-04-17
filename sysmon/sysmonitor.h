#ifndef SYSMONITOR_H
#define SYSMONITOR_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QFuture>
#include <QFutureWatcher>
#include <QTableWidgetItem>
#include <QtConcurrent/QtConcurrent>

#include "sensores.h"
#include "data_sensores.h"
#include "hardware.h"
#include "jsonmodel.h"

namespace Ui {
class sysmonitor;
}

class sysmonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit sysmonitor(QWidget *parent = 0);
    ~sysmonitor();

private slots:
    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::sysmonitor *ui;
    data_sensores *sensors;
    sensores *hilo_sens;
    QThread hilo_hw;
    hardware hw;
    QTimer *timer;
    bool is_numeric(const std::string x);
    QVector<QString> explore_dir_process(QString actual_dir, QString dir);
};

#endif // SYSMONITOR_H
