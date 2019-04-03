#include <QtGui>
#include "sysmonitor.h"

sysMonitor::sysMonitor(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);
}

void sysMonitor::getProcessInfo() {
    // 获取进程信息
    int counter;
    PROCESSENTRY32 currentProcess;
    currentProcess.dwSize = sizeof(currentProcess);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return;
    }

    BOOL bMore = Process32First(hSnapshot, &currentProcess);
    while (bMore) {
        DWORD pid = currentProcess.th32ProcessID;
        DWORD ppid = currentProcess.th32ParentProcessID;
        QString exeName =
            (QString::fromUtf16(reinterpret_cast<const unsigned short *>(
                currentProcess.szExeFile)));
        DWORD threads = currentProcess.cntThreads;

        if (!allProcesses.contains(pid))
            allProcesses.insert(pid, processInfo(pid, exeName, ppid, threads));

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
