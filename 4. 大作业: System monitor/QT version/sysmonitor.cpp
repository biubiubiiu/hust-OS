#include <QtGui>
#include "sysmonitor.h"

sysMonitor::sysMonitor(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);
    ui.processInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);    
    connect(ui.refreshProcessBtn, SIGNAL(clicked()), this, SLOT(ProcessInfoRefresh()));

    Chart *chart = new Chart;
    chart->setFunc(getCpuUsage);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    ui.cpuRatioChart->setChart(chart);
    ui.cpuRatioChart->setRenderHint(QPainter::Antialiasing);
}

void sysMonitor::getProcessInfo() {
    // 获取进程信息
    PROCESSENTRY32 currentProcess;
    currentProcess.dwSize = sizeof(currentProcess);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return;
    }

    int counter;

    BOOL bMore = Process32First(hSnapshot, &currentProcess);
    while (bMore) {
        DWORD pid = currentProcess.th32ProcessID;
        DWORD ppid = currentProcess.th32ParentProcessID;
        QString exeName =
            (QString::fromUtf16(reinterpret_cast<const unsigned short *>(
                currentProcess.szExeFile)));
        DWORD threads = currentProcess.cntThreads;
        counter = ui.processInfo->rowCount();
        ui.processInfo->insertRow(counter);
        ui.processInfo->setItem(counter, 0, new QTableWidgetItem(QString::number((pid))));
        ui.processInfo->setItem(counter, 1, new QTableWidgetItem(exeName));
        ui.processInfo->setItem(counter, 2, new QTableWidgetItem(QString::number(ppid)));
        ui.processInfo->setItem(counter, 3, new QTableWidgetItem(QString::number(threads)));

        bMore = Process32Next(hSnapshot, &currentProcess);
    }

    CloseHandle(hSnapshot);
}

void sysMonitor::getSystemInfo()
{
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);
    if(sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
            sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
        ui.osTypeLabel->setText("64-bit");
    }
    else {
        ui.osTypeLabel->setText("32-bit");
    }

    DWORD processorCoreNum = sysInfo.dwNumberOfProcessors;
    ui.coreNumLabel->setText(QString::number(processorCoreNum));
}

void sysMonitor::getOtherInfo()
{
    // 获取计算机名称
    ui.localHostNameLabel->setText(QHostInfo::localHostName());

    // 获取CPU型号
    QSettings *CPU = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",QSettings::NativeFormat);
    QString m_cpuDescribe = CPU->value("ProcessorNameString").toString();
    delete CPU;
    ui.cpuInfoLabel->setText(m_cpuDescribe);

    // 获取内存信息
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    double m_totalMem = statex.ullTotalPhys * 1.0/ GBytes;
    double m_freeMem = statex.ullAvailPhys * 1.0 / GBytes;

    QString m_memDescription = "可用" + QString::number(m_freeMem, 'f', 2) + " GB / 共" + QString::number(m_totalMem, 'f', 2) + " GB";
    ui.memoryInfoLabel->setText(m_memDescription);

    // 获取操作系统版本
    ui.osInfoLabel->setText(QSysInfo::prettyProductName());
}

qint64 CompareFileTime(const FILETIME &time1, const FILETIME &time2) {
    qint64 a = ((qint64(time1.dwHighDateTime) << 32) | time1.dwLowDateTime);
    qint64 b = ((qint64(time2.dwHighDateTime) << 32) | time2.dwLowDateTime);
    return (b - a);
}

double sysMonitor::getCpuUsage()
{
    static bool flag = false;

    static FILETIME idleTime;
    static FILETIME kernelTime;
    static FILETIME userTime;
    static FILETIME pre_idleTime;
    static FILETIME pre_kernelTime;
    static FILETIME pre_userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    if(!flag)
    {
        flag = true;
        pre_idleTime = idleTime;
        pre_kernelTime = kernelTime;
        pre_userTime = userTime;
        QThread::sleep(1);
        GetSystemTimes(&idleTime, &kernelTime, &userTime);
    }

    qint64 idle = CompareFileTime(pre_idleTime, idleTime);
    qint64 kernel = CompareFileTime(pre_kernelTime, kernelTime);
    qint64 user = CompareFileTime(pre_userTime, userTime);

    if(kernel + user == 0)
        return 0.0;

    double ratio = qAbs(double((kernel + user - idle)) * 100 / (kernel + user));

    pre_idleTime = idleTime;
    pre_kernelTime = kernelTime;
    pre_userTime = userTime;

    return ratio;
}

void sysMonitor::ProcessInfoRefresh()
{
    ui.processInfo->model()->removeRows(0, ui.processInfo->rowCount());
    getProcessInfo();
}
