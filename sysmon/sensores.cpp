#include "sensores.h"

sensores::sensores(data_sensores *cont, QObject *parent):
    QThread(parent),
    buffer(cont){
}

void sensores::run(void){
    QString name, aux, data;
    bool found= false;

    while(1){
        sleep(1);
        QDir dir("/sys/class/hwmon");

        for(auto directory: dir.entryList(QDir::Dirs, QDir::NoSort)){
            found = false;
            QString directorio_actual("/sys/class/hwmon/" + directory);

            if(!(directorio_actual== "/sys/class/hwmon/." && directorio_actual == "/sys/class/hwmon/..")){
                QDir directorio_aux(directorio_actual);

                for(auto file: directorio_aux.entryList(QDir::Files, QDir::NoSort)){
                    QFile fichero_actual(directorio_actual + "/" + file);

                    if(!fichero_actual.open(QIODevice::ReadOnly | QIODevice::Text)) return;

                    QTextStream in(&fichero_actual);
                    aux = in.readAll();
                    data = aux.mid(0,aux.lastIndexOf('\n'));

                    if(!found){
                        if(file == "name"){
                            name = data;
                            found = true;
                        }
                    }
                    else if(file.contains("temp") or file.contains("fan")){
                        aux = name + " : " + file;
                        QPair<QString,QString> pair(aux, data);
                        buffer->insert_info(pair);
                    }
                    fichero_actual.close();
                }
            }
        }
        emit refreshInfo(0);
    }
}
int sensores::get_buffer_size(void){
    return buffer->get_counter();
}
