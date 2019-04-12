#include <QtGui>
#include "sysmonitor.h"

sysMonitor::sysMonitor(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);
//    ui.processInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    cpuChart = new Chart;
    ui.cpuUsageChart->setChart(cpuChart);
    ui.cpuUsageChart->setRenderHint(QPainter::Antialiasing);

    memChart = new Chart;
    ui.memoryUsageChart->setChart(memChart);
    ui.memoryUsageChart->setRenderHint(QPainter::Antialiasing);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(chartRefresh()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(ProcessInfoRefresh()));
    m_timer->setInterval(1000);
    m_timer->start();

    ui.processInfo->setColumnWidth(0, 65);
    ui.processInfo->setColumnWidth(1, 250);
    ui.processInfo->setColumnWidth(2, 100);
    ui.processInfo->setColumnWidth(3, 100);
    ui.processInfo->setColumnWidth(4, 100);

    connect(ui.processInfo, SIGNAL(cellEntered(int, int)), this, SLOT(handleCellEntered(int, int)));
}

sysMonitor::~sysMonitor()
{

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

        HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION |
                                        PROCESS_VM_READ,
                                        FALSE, pid);
        PROCESS_MEMORY_COUNTERS pmc;
        pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);
        GetProcessMemoryInfo(hProc, &pmc, sizeof(pmc));

        QString elidedName = getElidedText(ui.processInfo->font(), exeName, ui.processInfo->columnWidth(1));
        counter = ui.processInfo->rowCount();
        ui.processInfo->insertRow(counter);
        ui.processInfo->setItem(counter, 0, new QTableWidgetItem(QString::number((pid))));
        ui.processInfo->setItem(counter, 1, new QTableWidgetItem(elidedName));
        ui.processInfo->item(counter, 1)->setToolTip(exeName);
        ui.processInfo->setItem(counter, 2, new QTableWidgetItem(QString::number(ppid)));
        ui.processInfo->setItem(counter, 3, new QTableWidgetItem(QString::number(threads)));
        ui.processInfo->setItem(counter, 4, new QTableWidgetItem(QString::number(pmc.WorkingSetSize / KBytes) + "K"));

        bMore = Process32Next(hSnapshot, &currentProcess);
        CloseHandle(hProc);
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


double sysMonitor::getMemoryUsage()
{
    // 获取内存信息
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    double m_totalMem = statex.ullTotalPhys * 1.0/ GBytes;
    double m_freeMem = statex.ullAvailPhys * 1.0 / GBytes;
    double memUsage = 100 * (1 - (statex.ullAvailPhys * 1.0 / statex.ullTotalPhys));

    ui.memoryUsageLabel->setText(QString::number(memUsage, 'f', 2) + "%\t\t"
                                + QString::number(m_freeMem, 'f', 2) + "GB available / "
                                + QString::number(m_totalMem, 'f', 2) + "GB total");

    return memUsage;
}

void sysMonitor::getDiskInfo()
{
    QString diskDescription = "";
    QFileInfoList list = QDir::drives();
    foreach(QFileInfo dir, list)
    {
        QString dirName = dir.absolutePath();
        dirName.remove("/");
        LPCWSTR lpcwstrDriver = (LPCWSTR)dirName.utf16();
        ULARGE_INTEGER liFreeBytesAvilale, liTotalBytes, liTotalFreeBytes;
        if(GetDiskFreeSpaceEx(lpcwstrDriver, &liFreeBytesAvilale, &liTotalBytes, &liTotalFreeBytes))
        {
            QString free = QString::number(1.0 * liTotalFreeBytes.QuadPart / GBytes, 'f', 1);
            free.append('G');
            QString all = QString::number(1.0 * liTotalBytes.QuadPart / GBytes, 'f', 1);
            all.append('G');

            QString str = QString("%1 %2/%3     ").arg(dirName, free, all);
            diskDescription += str;
        }
    }
    ui.diskInfoLabel->setText(diskDescription);
}

void sysMonitor::ProcessInfoRefresh()
{
    ui.processInfo->model()->removeRows(0, ui.processInfo->rowCount());
    getProcessInfo();
}

void sysMonitor::chartRefresh()
{
    double cpuUsage = getCpuUsage();
    cpuChart->append(cpuUsage);
    cpuChart->refresh();

    ui.cpuUsageLabel->setText(QString::number(cpuUsage, 'f', 2) + "%");

    double memUsage = getMemoryUsage();
    memChart->append(memUsage);
    memChart->refresh();
}

void sysMonitor::handleCellEntered(int row, int column)
{
    QTableWidgetItem *item = ui.processInfo->item(row, column);
    if(item == nullptr)
        return;
    if (column == 1)
        QToolTip::showText(QCursor::pos(), item->toolTip());
    else
        QToolTip::showText(QCursor::pos(), item->text());
}
