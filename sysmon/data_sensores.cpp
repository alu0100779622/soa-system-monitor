#include "data_sensores.h"

data_sensores::data_sensores():
    counter(0){}

data_sensores::~data_sensores(){
}

int data_sensores::get_counter(void){
    return counter;
}

void data_sensores::insert_info(const QPair<QString,QString> &pair){
    mutex.lock();
    info.push_back(pair);
    counter++;
    mutex.unlock();
}

QPair<QString, QString> data_sensores::extract_info(){
    if(counter != 0){
        mutex.lock();
        QPair<QString, QString> datos = info[info.size()-1];
        info.pop_back();
        counter--;
        mutex.unlock();
        return datos;
    }
    else{
        QPair<QString, QString> datos;
        return datos;
    }
}

