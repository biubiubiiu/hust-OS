#include <QtGui>
#include "sysmonitor.h"

sysMonitor::sysMonitor(QWidget *parent) : QWidget(parent) {
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 去掉最大化按钮
    setFixedSize(720, 576);     // 设置窗口大小不可改变
    ui.setupUi(this);

    // 初始化 ‘cpu’页 的cpu使用率图表
    cpuChart = new Chart;
    ui.cpuUsageChart->setChart(cpuChart);
    ui.cpuUsageChart->setRenderHint(QPainter::Antialiasing);

    // 初始化 ‘内存’ 页的内存使用率图表
    memChart = new Chart;
    ui.memoryUsageChart->setChart(memChart);
    ui.memoryUsageChart->setRenderHint(QPainter::Antialiasing);

    // 启动计时器，每隔1000ms更新一次信息
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(refresh()));
    m_timer->setInterval(1000);
    m_timer->start();

    // 设置 ‘进程’ 页中每一列的宽度
    // 开启了 horizonalHeaderStretchLastSection， 不必设置最后一列的宽度
    ui.processInfo->setColumnWidth(0, 65);
    ui.processInfo->setColumnWidth(1, 250);
    ui.processInfo->setColumnWidth(2, 90);
    ui.processInfo->setColumnWidth(3, 90);
    ui.processInfo->setColumnWidth(4, 90);

    connect(ui.processInfo, SIGNAL(cellEntered(int, int)), this, SLOT(handleCellEntered(int, int)));
    connect(ui.processInfo, SIGNAL(itemSelectionChanged()), this, SLOT(handleSelectionChanged()));
    connect(ui.searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(searchProcess(const QString&)));
    connect(ui.killProcessBtn, SIGNAL(clicked()), this, SLOT(killProcess()));
    connect(ui.diskRefreshBtn, SIGNAL(clicked()), this, SLOT(diskInfoRefresh()));

    ui.killProcessBtn->setEnabled(false);
}

sysMonitor::~sysMonitor()
{

}

/* 获取 ‘进程’ 页内容 */
void sysMonitor::getProcessInfo() {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    HANDLE hProcessSnap;
    HANDLE hProcess;

    QString priority;

    // 获得进程快照
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    int counter;

    if(!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return;
    }

    do {
        DWORD pid = pe32.th32ProcessID;
        DWORD ppid = pe32.th32ParentProcessID;
        QString exeName =
            (QString::fromUtf16(reinterpret_cast<const unsigned short *>(
                pe32.szExeFile)));
        DWORD threads = pe32.cntThreads;
        priority = QString::number(pe32.pcPriClassBase);
        DWORD workingSetSize;

        // 尝试获取进程句柄
        // warning: 由于Windows对访问权限的（严重）控制
        // 会由于权限不足导致无法返回进程句柄
        // 获取进程内存，用户名等操作无法完成
        // 没有解决办法
        hProcess = OpenProcess(PROCESS_ALL_ACCESS,
                               FALSE, pid);


        // 当访问权限不足时，返回hProcess为NULL
        if(hProcess == NULL)
        {
            // 设置进程占用内存为0，表示无法获取
            workingSetSize = 0;
        }
        else
        {
            // 获取进程占用内存
            PROCESS_MEMORY_COUNTERS pmc;
            pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);
            GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
            workingSetSize = pmc.WorkingSetSize;

            // 获取进程用户名
//            HANDLE hToken;
//            DWORD dwSize = 0;
//            if(OpenProcessToken(hProcess, TOKEN_QUERY, &hToken) == TRUE)
//            {
//                if(GetTokenInformation(hToken, TokenUser, NULL, 0, &dwSize) == TRUE)
//                {
//                    PTOKEN_USER pTokenUser = (PTOKEN_USER)new BYTE[dwSize];
//                    if(GetTokenInformation(hToken, TokenUser, pTokenUser, dwSize, &dwSize) == TRUE)
//                    {
//                        BOOL bLookupSid;
//                        SID_NAME_USE snu;
//                        TCHAR szUserName[1024];
//                        int nLen = sizeof(szUserName) / sizeof(TCHAR);
//                        DWORD dwUserSize = sizeof(szUserName) / sizeof(TCHAR);
//                        TCHAR szDomain[1024];
//                        DWORD cbDomain = sizeof(szDomain) / sizeof(TCHAR);
//                        bLookupSid = LookupAccountSid(NULL, pTokenUser->User.Sid,
//                                                      szUserName, &dwUserSize,
//                                                      szDomain, &cbDomain, &snu);
//                        if(bLookupSid)
//                            processUsername = QString::fromUtf16(reinterpret_cast<const unsigned short *>(szUserName));
//                        else
//                            processUsername = "lookupsid error";
//                    }
//                }
//                else
//                    processUsername = (GetLastError() == ERROR_INSUFFICIENT_BUFFER?"shit":"");
//            }
//            else
//                processUsername = "open process token error";


        }
        // 获取进程优先级
//        dwPriorityClass = GetPriorityClass(hProcess);
//        switch(dwPriorityClass)
//        {
//        case ABOVE_NORMAL_PRIORITY_CLASS:
//            priority = "above normal";
//            break;
//        case BELOW_NORMAL_PRIORITY_CLASS:
//            priority = "below normal";
//            break;
//        case HIGH_PRIORITY_CLASS:
//            priority = "high";
//            break;
//        case IDLE_PRIORITY_CLASS:
//            priority = "idle";
//            break;
//        case NORMAL_PRIORITY_CLASS:
//            priority = "normal";
//            break;
//        case REALTIME_PRIORITY_CLASS:
//            priority = "realtime";
//            break;
//        case 0:
//            priority = "unknown";
//            break;
//        }

        // 进程名和优先级部分可能会出现文本过长问题
        // 这里获取处理后的字符串
        QString elidedName = getElidedText(ui.processInfo->font(), exeName, ui.processInfo->columnWidth(1));
        QString elidedPriority = getElidedText(ui.processInfo->font(), priority, ui.processInfo->columnWidth(5));
        counter = ui.processInfo->rowCount();
        ui.processInfo->insertRow(counter);
        ui.processInfo->setItem(counter, 0, new QTableWidgetItem(QString::number((pid))));
        ui.processInfo->setItem(counter, 1, new QTableWidgetItem(elidedName));
        ui.processInfo->setItem(counter, 2, new QTableWidgetItem(QString::number(ppid)));
        ui.processInfo->setItem(counter, 3, new QTableWidgetItem(QString::number(threads)));
        ui.processInfo->setItem(counter, 4, new QTableWidgetItem(QString::number(workingSetSize * 1.0 / MBytes, 'f', 1) + "MB"));
        ui.processInfo->setItem(counter, 5, new QTableWidgetItem(elidedPriority));

        // 如果出现文本过长，设置tooltip提示
        if(elidedName != exeName)
            ui.processInfo->item(counter, 1)->setToolTip(exeName);
        else
            ui.processInfo->item(counter, 1)->setToolTip("");
        if(elidedPriority != priority)
            ui.processInfo->item(counter, 5)->setToolTip(priority);
        else
            ui.processInfo->item(counter, 5)->setToolTip("");

        ui.processInfo->item(counter, 2)->setTextAlignment(Qt::AlignCenter);
        ui.processInfo->item(counter, 3)->setTextAlignment(Qt::AlignCenter);
        ui.processInfo->item(counter, 4)->setTextAlignment(Qt::AlignCenter);
        ui.processInfo->item(counter, 5)->setTextAlignment(Qt::AlignCenter);

        CloseHandle(hProcess);

    } while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

/* 获取 ‘系统’ 页中相关信息 */
void sysMonitor::getSystemInfo()
{
    // 判断操作系统位数
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);
    if(sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
            sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
        ui.osTypeLabel->setText("64-bit");
    }
    else {
        ui.osTypeLabel->setText("32-bit");
    }

    // 获取设备运行时间
    DWORD ticks = GetTickCount();
    ui.uptimeLabel->setText(transformTime(ticks));

    // 获取计算机名称
    ui.localHostNameLabel->setText(QHostInfo::localHostName());

    // 获取操作系统版本
    ui.osInfoLabel->setText(QSysInfo::prettyProductName());
}

/* 获取 ‘cpu’ 页中相关信息 */
void sysMonitor::getCpuInfo()
{
    // 获取cpu型号
    // 实质是读取注册表内容
    QSettings *CPU = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",QSettings::NativeFormat);
    QString m_cpuDescribe = CPU->value("ProcessorNameString").toString();
    delete CPU;
    ui.cpuInfoLabel->setText(m_cpuDescribe);

    // 获取核数
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);
    DWORD processorCoreNum = sysInfo.dwNumberOfProcessors;
    ui.coreNumLabel->setText(QString::number(processorCoreNum));
}

/*
 * 功能：计算两个 filetime 的差值
 */
qint64 CompareFileTime(const FILETIME &time1, const FILETIME &time2) {
    // 先将 filetime 转换为64位整数
    qint64 a = ((qint64(time1.dwHighDateTime) << 32) | time1.dwLowDateTime);
    qint64 b = ((qint64(time2.dwHighDateTime) << 32) | time2.dwLowDateTime);
    return (b - a);
}

/*
 * 返回当前的cpu使用率
 * 返回值主要用来绘制cpu使用率图表
 * cpu使用率计算方法： ratio = (kernel + user - idle) / (kernel + user)
 */
double sysMonitor::getCpuUsage()
{
    // 记录是否是第一次获取数据
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

/*
 * 返回当前内存使用率
 * 返回值主要用来绘制内存使用率图表
 */
double sysMonitor::getMemoryUsage()
{
    // 获取内存信息
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    double m_totalMem = statex.ullTotalPhys * 1.0/ GBytes;
    double m_freeMem = statex.ullAvailPhys * 1.0 / GBytes;
    double memUsage = 100 * (1 - (statex.ullAvailPhys * 1.0 / statex.ullTotalPhys));

    // 顺便把 label 也改了
    ui.totalMemoryLabel->setText(QString::number(m_totalMem, 'f', 1) + "  GB");
    ui.inUseMemoryLabel->setText(QString::number(m_totalMem - m_freeMem, 'f', 1) + " GB");
    ui.availableMemoryLabel->setText(QString::number(m_freeMem, 'f', 1) + " GB");
    ui.memoryUsageLabel->setText(QString::number(memUsage, 'f', 2) + "%");

    return memUsage;
}

/* 读取硬盘信息 */
void sysMonitor::getDiskInfo()
{
    QString diskDescription = "";
    // 获取所有盘符
    QFileInfoList list = QDir::drives();
    // 遍历盘符列表
    foreach(QFileInfo dir, list)
    {
        QString dirName = dir.absolutePath();
        dirName.remove("/");
        LPCWSTR lpcwstrDriver = (LPCWSTR)dirName.utf16();
        ULARGE_INTEGER liFreeBytesAvilale, liTotalBytes, liTotalFreeBytes;
        if(GetDiskFreeSpaceEx(lpcwstrDriver, &liFreeBytesAvilale, &liTotalBytes, &liTotalFreeBytes))
        {
            QString free = QString::number(1.0 * liTotalFreeBytes.QuadPart / GBytes, 'f', 1);
            free += 'G';
            QString all = QString::number(1.0 * liTotalBytes.QuadPart / GBytes, 'f', 1);
            all += 'G';
            QString usage = QString::number(100.0 * liTotalFreeBytes.QuadPart / liTotalBytes.QuadPart, 'f', 2);
            usage += '%';

            QString str = QString("%1\t%2 / %3\t\t\t%4 used\n\n").arg(dirName, free, all, usage);
            diskDescription += str;
        }
    }
    ui.diskInfoLabel->setText(diskDescription);
}

/* 刷新 ‘进程’ 页内容 */
void sysMonitor::ProcessInfoRefresh()
{
    bool flag = false;
    int selectedRow = 0;
    // 记录原来的滚动条位置
    int currentValue = ui.processInfo->verticalScrollBar()->value();
    // 判断当前有没有选择某一行
    if(!ui.processInfo->selectedItems().empty())
    {
        // 如果有，记录选择的行数
        selectedRow = ui.processInfo->selectedItems().first()->row();
        flag = true;
    }
    ui.processInfo->model()->removeRows(0, ui.processInfo->rowCount());
    getProcessInfo();
    // 刷新内容后，原来的选择信息会丢失，这里重新设置回原来的选择
    if(flag)
        ui.processInfo->selectRow(selectedRow);
    // 执行selectRow后，会自动滚动到所选行附近
    // 通过恢复滚动条位置，解决上述问题
    ui.processInfo->verticalScrollBar()->setValue(currentValue);
}

/* 刷新硬盘信息 */
void sysMonitor::diskInfoRefresh()
{
    getDiskInfo();
}

/* 刷新图表 */
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

/* 刷新系统运行时间 */
void sysMonitor::uptimeRefresh()
{
    DWORD ticks = GetTickCount();
    ui.uptimeLabel->setText(transformTime(ticks));
}

void sysMonitor::refresh()
{
    ProcessInfoRefresh();
    chartRefresh();
    uptimeRefresh();
}

/*
 * 功能：对于 ‘进程’ 页中过长的信息，实现鼠标悬停显示完整内容
 * 参数：
 * -row:鼠标所在单元的行
 * -column:鼠标所在单元的列
 */
void sysMonitor::handleCellEntered(int row, int column)
{
    if(column != 1 && column != 5)
        return;
    QTableWidgetItem *item = ui.processInfo->item(row, column);
    if(item == nullptr)
        return;
    if (item->toolTip() != "")
        QToolTip::showText(QCursor::pos(), item->toolTip());
}

/*
 * 当 ‘进程’ 页选择发生改变时触发
 * 功能： 当选择为空时，设置 KillProcess 按钮为不可选中状态
 */
void sysMonitor::handleSelectionChanged()
{
    QList<QTableWidgetItem *> items = ui.processInfo->selectedItems();
    if(items.empty())
        ui.killProcessBtn->setEnabled(false);
    else
        ui.killProcessBtn->setEnabled(true);
}

/*
 * 功能：实现 ‘进程’ 页中的搜索功能，搜索方式为全匹配搜索
 * 参数：
 * -key：搜索关键字
 */
void sysMonitor::searchProcess(const QString &key)
{
    if(key == "")
        ui.processInfo->clearSelection();
    QList<QTableWidgetItem *> items = ui.processInfo->findItems(key, Qt::MatchContains);
    if(!items.empty())
    {
        int first = items.first()->row();
        ui.processInfo->selectRow(first);
    }
    else
        ui.processInfo->clearSelection();
}

/*
 * 功能：终止 ‘进程’页中选择的进程
 */
void sysMonitor::killProcess()
{
    QList<QTableWidgetItem *> items = ui.processInfo->selectedItems();
    if(items.empty())
        return;
    int row = items.first()->row();
    DWORD pid = ui.processInfo->item(row, 0)->text().toULong();
    HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if(hProc == NULL)
        return;
    if(TerminateProcess(hProc, 0) == TRUE)
    {
        ProcessInfoRefresh();
        ui.processInfo->clearSelection();
    }
    CloseHandle(hProc);
}
