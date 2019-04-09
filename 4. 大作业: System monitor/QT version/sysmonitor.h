#ifndef SYSMONITOR_H
#define SYSMONITOR_H

#include <windows.h>
#include <tlhelp32.h>
#include <lm.h>

#include <QWidget>
#include <QSysInfo>
#include <QHostInfo>
#include <QDebug>
#include <QtCharts>
#include <QTimer>

#include "chart.h"
#include "ui_sysmonitor.h"

QT_CHARTS_USE_NAMESPACE

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
    static double getCpuUsage();

private:
    Ui_sysMonitor ui;

private slots:
    void ProcessInfoRefresh();
};

#endif // SYSMONITOR_H
