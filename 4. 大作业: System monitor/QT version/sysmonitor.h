#ifndef SYSMONITOR_H
#define SYSMONITOR_H

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <lm.h>

#include <QWidget>
#include <QSysInfo>
#include <QHostInfo>
#include <QDebug>
#include <QtCharts>
#include <QTimer>
#include <QMouseEvent>
#include <QToolTip>

#include "chart.h"
#include "ui_sysmonitor.h"
#include "utils.h"

QT_CHARTS_USE_NAMESPACE

#define GBytes (1024 * 1024 * 1024)
#define MBytes (1024 * 1024)
#define KBytes (1024)

class sysMonitor : public QWidget
{
    Q_OBJECT

public:
    sysMonitor(QWidget *parent = nullptr);

virtual ~sysMonitor();

public:
    void getProcessInfo();
    void getSystemInfo();
    void getOtherInfo();
    void getDiskInfo();
    double getCpuUsage();
    double getMemoryUsage();

private:
    Ui_sysMonitor ui;
    Chart *cpuChart;
    Chart *memChart;
    QTimer *m_timer;

private slots:
    void ProcessInfoRefresh();
    void chartRefresh();
    void handleCellEntered(int, int);
};

#endif // SYSMONITOR_H
