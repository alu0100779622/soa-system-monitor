#-------------------------------------------------
#
# Project created by QtCreator 2017-03-11T20:04:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysmon
TEMPLATE = app


SOURCES += main.cpp\
        sysmonitor.cpp \
    sensores.cpp \
    data_sensores.cpp \
    hardware.cpp \
    jsonmodel.cpp

HEADERS  += sysmonitor.h \
    sensores.h \
    data_sensores.h \
    hardware.h \
    jsonmodel.h

FORMS    += sysmonitor.ui

CONFIG   += c++11
