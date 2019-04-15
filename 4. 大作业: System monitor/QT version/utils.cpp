#include "utils.h"

/*
 * 功能：返回隐藏过长内容后的字符串
 * 参数：
 * -font：字体信息
 * -str：源字符串
 * -maxWidth：最大显示宽度
 */
QString getElidedText(QFont font, QString str, int maxWidth)
{
    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);
    if(width >= maxWidth)
        str = fontWidth.elidedText(str, Qt::ElideRight, maxWidth);
    return str;
}

/*
 * 功能：将 cpu tick 的次数转换为 dd-hh-mm-ss 的字符串形式
 * 参数：
 * -tick：cpu 滴答数
 */
QString transformTime(unsigned long tick)
{
    unsigned long seconds = tick / 1000;
    unsigned long minute = 0, hour = 0, day = 0;
    if(seconds >= 60)
    {
        minute = seconds / 60;
        seconds %= 60;
    }
    if(minute >= 60)
    {
        hour = minute / 60;
        minute %= 60;
    }
    if(hour >= 24)
    {
        day = hour / 24;
        hour %= 24;
    }
    QString ret = QString("%1:%2:%3:%4").arg(day, 2, 10, QChar('0'))
                                        .arg(hour, 2, 10, QChar('0'))
                                        .arg(minute, 2, 10, QChar('0'))
                                        .arg(seconds, 2, 10, QChar('0'));
    return ret;
}

BOOL SetPrivilege(
                  HANDLE hToken,          // access token handle
                  LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
                  BOOL bEnablePrivilege   // to enable or disable privilege
                  )
{
    TOKEN_PRIVILEGES tp;
    LUID luid;
    if ( !LookupPrivilegeValue(
        NULL,            // lookup privilege on local system
        lpszPrivilege,   // privilege to lookup
        &luid ) )        // receives LUID of privilege
    {
        printf("LookupPrivilegeValue error: %u/n", GetLastError() );
        return FALSE;
    }
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if ( bEnablePrivilege )
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
        tp.Privileges[0].Attributes = 0;
    // Enable the privilege or disable all privileges.
    if ( !AdjustTokenPrivileges(
        hToken,
        FALSE,
        &tp,
        sizeof(TOKEN_PRIVILEGES),
        (PTOKEN_PRIVILEGES) NULL,
        (PDWORD) NULL) )
    {
        printf("AdjustTokenPrivileges error: %u/n", GetLastError() );
        return FALSE;
    }
    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
    {
        printf("The token does not have the specified privilege. /n");
        return FALSE;
    }
    return TRUE;
}

HANDLE getProcessHandle(DWORD dwProcessId)
{
    HANDLE hToken;
    bool flag = OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken );
    if( !flag )
    {
        DWORD err = GetLastError();
        printf( "OpenProcessToken error:%d", err );
    }
    SetPrivilege( hToken, SE_DEBUG_NAME, true );
    CloseHandle(hToken);
    return OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, dwProcessId);
}

bool EnableDebugPrivilege()
{
    HANDLE hToken;
    LUID sedebugnameValue;
    TOKEN_PRIVILEGES tkp;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        return FALSE;
    }
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
    {
        CloseHandle(hToken);
        return false;
    }
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = sedebugnameValue;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
    {
        CloseHandle(hToken);
        return false;
    }
    return true;
}
