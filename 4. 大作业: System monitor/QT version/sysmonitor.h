#ifndef SYSMONITOR_H
#define SYSMONITOR_H

#include <windows.h>
#include <tlhelp32.h>

#include <QWidget>
#include <QMap>


#include "ui_sysmonitor.h"

struct processInfo
{
    DWORD pid;
    QString name;
    DWORD ppid;
    DWORD threads;
    processInfo(DWORD &a, QString &str, DWORD &b, DWORD &c)
    {
        pid = a;
        name = str;
        ppid = b;
        threads = c;
    }
};

class sysMonitor : public QWidget
{
    Q_OBJECT

public:
    sysMonitor(QWidget *parent = nullptr);

public:
    void getProcessInfo();

private:
    QMap<DWORD, processInfo> allProcesses;

    Ui_sysMonitor ui;
};

#endif // SYSMONITOR_H
