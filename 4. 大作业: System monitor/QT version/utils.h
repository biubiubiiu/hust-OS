#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFont>
#include <QFontMetrics>
#include <windows.h>

QString getElidedText(QFont font, QString str, int maxWidth);
QString transformTime(unsigned long tick);
BOOL setPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
HANDLE getProcessHandle(DWORD dwProcessId);
bool EnableDebugPrivilege();

#endif // UTILS_H
