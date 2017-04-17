#include "sysmonitor.h"
#include "ui_sysmonitor.h"

#include "sensores.h"

sysmonitor::sysmonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sysmonitor)
{
    ui->setupUi(this);
    sensors = new data_sensores();
    hilo_sens = new sensores(sensors,this);
    connect(hilo_sens, SIGNAL(refreshInfo(int)), this, SLOT(on_tabWidget_tabBarClicked(int)));
    hilo_sens->start();

    timer = new QTimer();
    timer->start(5000);
    connect(timer, SIGNAL(timeout()), SLOT(on_tabWidget_tabBarClicked(int)));

    connect(&hw,SIGNAL(ejecute(int)),this,SLOT(on_tabWidget_tabBarClicked(int)));
    hw.moveToThread(&hilo_hw);
    connect(&hilo_hw,SIGNAL(started()),&hw,SLOT(lshw()));
    hilo_hw.start();
}

sysmonitor::~sysmonitor()
{
    hilo_sens->quit();
    hilo_sens->deleteLater();
    delete ui;
}

void sysmonitor::on_tabWidget_tabBarClicked(int index)
{
    QPair<QString,QString> text;
    switch(index){
        case 0:
        ui->text_sensores->clear();
        for(int i = 0; i < hilo_sens->get_buffer_size(); i++){
            text = sensors->extract_info();
            ui->text_sensores->insertPlainText(text.first + '\t' + text.second + '\n');
        }

        break;

    case 1:{
            QByteArray aux = hw.transferenciadatos();
            QJsonModel * model = new QJsonModel;
            ui->tree_hw->setColumnWidth(0,100);
            ui->tree_hw->setModel(model);
            model->loadJson(aux);
    }
        break;

    case 2:{
        QDir directory("/proc");
        ui->table_procesos->setRowCount(0);

        for(auto dir:directory.entryList(QDir::Dirs, QDir::NoSort)){
            std::string aux_string = dir.toUtf8().constData();

            if(is_numeric(aux_string)){
                QString actual_dir("/proc/" + dir);
                QFuture<QVector<QString>> function = QtConcurrent::run(this, &sysmonitor::explore_dir_process, actual_dir, dir);
                QFutureWatcher<QVector<QString>> *watcher = new QFutureWatcher<QVector<QString>>;
                watcher->setFuture(function);

                connect(watcher, &QFutureWatcher<QVector<QString>>::finished, [this,watcher](){
                    QVector<QString> aux;
                    aux = watcher->result();
                    int j = ui->table_procesos->rowCount();
                    ui->table_procesos->setRowCount(ui->table_procesos->rowCount()+1);

                    for(int i = 0; i < 5; i++){
                        ui->table_procesos->setItem(j-1,i,new QTableWidgetItem (aux[i]));
                    }
                    watcher->deleteLater();
                });
            }
        }
    }
        break;

    default:
        break;

    }
}

bool sysmonitor::is_numeric(const std::string x){
    return !x.empty() && std::find_if(x.begin(), x.end(), [](char c){
        return !std::isdigit(c);
    }) == x.end();
}

QVector<QString> sysmonitor::explore_dir_process(QString dir, QString PID){
    QVector<QString> row;
    QString cmd, status, name, threads;
    QFile file_aux1(dir + "/cmdline"), file_aux2(dir + "/status");
    QTextStream in1(&file_aux1), in2(&file_aux2);

    row.push_back(PID);

    if(file_aux1.open(QIODevice::ReadOnly)){
        cmd = in1.readAll();
        row.push_back(cmd);
    }

    if(file_aux2.open(QIODevice::ReadOnly)){
        status = in2.readAll();
        name = status.mid(status.lastIndexOf("Name:"), status.indexOf("\n"));
        name = name.remove("Name:\t");
        threads = status.mid(status.lastIndexOf("Threads:"),10);
        threads = threads.remove("Threads:\t");
        status = status.mid(status.lastIndexOf("State:"), 8);
        status = status.remove("State:\t");
        row.push_back(name);
        row.push_back(threads);
        row.push_back(status);
    }

    file_aux1.close();
    file_aux2.close();

    return row;
}
