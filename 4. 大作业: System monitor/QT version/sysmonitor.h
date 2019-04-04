#ifndef SYSMONITOR_H
#define SYSMONITOR_H

#include <windows.h>
#include <tlhelp32.h>
#include <lm.h>

#include <QWidget>
#include <QSysInfo>
#include <QHostInfo>
#include <QDebug>

#include "ui_sysmonitor.h"

#define GBytes (1024 * 1024 * 1024)
#define MBytes (1024 * 1024)
#define KBytes (1024)

class sysMonitor : public QWidget
{
    Q_OBJECT

public:
    sysMonitor(QWidget *parent = nullptr);

public:
    void getProcessInfo();
    void getSystemInfo();
    void getOtherInfo();

private:
    Ui_sysMonitor ui;
};

#endif // SYSMONITOR_H
