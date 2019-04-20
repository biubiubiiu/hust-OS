#include <QApplication>
#include "sysmonitor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    sysMonitor sm;
    sm.show();
    sm.getProcessInfo();
    sm.getSystemInfo();
    sm.getCpuInfo();
    sm.getDiskInfo();

    return a.exec();
}
