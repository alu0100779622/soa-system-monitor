#include "sysmonitor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sysmonitor w;
    w.show();

    return a.exec();
}
