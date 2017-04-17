#include "hardware.h"


void hardware::lshw(){

      QString program = "lshw";
      QStringList arguments;
      arguments << "-json";

      QProcess *myProcess = new QProcess(this);
      myProcess->start(program,arguments);
      myProcess->waitForFinished();
      myProcess->readyRead();
      datoslshw = myProcess->readAllStandardOutput();
      emit ejecute(2);
}

QByteArray hardware::transferenciadatos(){
    return datoslshw;

//    ui->setupUi(this);
//    ui->tabWidget->setTabText(0,"Procesos");
//    ui->tabWidget->setTabText(1,"Red");
//    ui->tabWidget->setTabText(2,"Sensores");
//    ui->tabWidget->setTabText(3,"Hardware");


}
