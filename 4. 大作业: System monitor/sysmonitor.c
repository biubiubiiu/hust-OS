/* for visual studio*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
/*
 *   warning：<winsocks.h> should be import before <Windows.h>
 *   warning：<Windows.h> should be import before <tlhelp32.h>
 */
#include <winsock2.h>
#include <Windows.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <tlhelp32.h>

#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#pragma warning(disable: 4996)

/*
 *   get process information
 *   referencing from: https://www.cnblogs.com/kuangke/p/6259350.html
 *                     https://blog.csdn.net/zjx_cfbx/article/details/82390064
 */
void getProcessInfo(void) {
    int countProcess = 0;
    PROCESSENTRY32 currentProcess;
    currentProcess.dwSize = sizeof(currentProcess);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf("CreateToolhelp32snapshot() failed!\n");
        return;
    }

    BOOL bMore = Process32First(hSnapshot, &currentProcess);
    while (bMore) {
        // 获取单一进程内存占用信息
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE,
                                      currentProcess.th32ProcessID);
        PROCESS_MEMORY_COUNTERS pmc = {0};
        pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);
        GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
        printf("PID=%5u\tMemory Usage=%8uKB\n", currentProcess.th32ProcessID,
               pmc.WorkingSetSize / 1024);
        CloseHandle(hProcess);

        // 获取进程列表
        // printf("PID=%5u\tPName= %s\tthread number:%d\tparent process:%d\n",
        //        currentProcess.th32ProcessID, currentProcess.szExeFile,
        //        currentProcess.cntThreads,
        //        currentProcess.th32ParentProcessID);
        bMore = Process32Next(hSnapshot, &currentProcess);
        countProcess++;
    }

    CloseHandle(hSnapshot);
    printf("there are %d processes running\n", countProcess);
    getchar();
    return;
}

/*
 *   get host information including hostname and IP address(es)
 *   referencing from: https://blog.csdn.net/wynter_/article/details/52529685
 */
void getIP() {
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 0), &WSAData)) {
        printf("WSAStartup failed %d \n", WSAGetLastError());
        return;
    }

    char hostName[256];
    if (gethostname(hostName, sizeof(hostName))) {
        printf("Error: %u \n", WSAGetLastError());
        return;
    }
    printf("Host name:\t%s\n", hostName);

    struct hostent *host = gethostbyname(hostName);

    char **pptr;
    for (pptr = host->h_aliases; *pptr != NULL; pptr++)
        printf("alias: %s\n", *pptr);

    switch (host->h_addrtype) {
        case AF_INET:
        case AF_INET6:
            pptr = host->h_addr_list;
            for (; *pptr != NULL; pptr++) {
                printf("address:\t%s\n",
                       inet_ntoa(*(struct in_addr *)host->h_addr_list));
            }
            break;

        default:
            break;
    }
    WSACleanup();
}

/*   get operating system information
 *   including version and system bit
 *   bug: Windows 8.1 or Windows 10 will return the Windows 8 OS version value
 * (6.2).
 */
void getSysInfo() {
    // 获取系统位数
    SYSTEM_INFO sysInfo;
    BOOL is32Bit;
    GetNativeSystemInfo(&sysInfo);
    if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
        sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
        is32Bit = FALSE;
    else
        is32Bit = TRUE;
    // 核数
    DWORD processorCoreNum;
    processorCoreNum = sysInfo.dwNumberOfProcessors;
    printf("core number:%2u", processorCoreNum);
    // 获取系统版本信息
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
            printf("Windows 2000\n");
        else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
            printf("Windows XP\n");
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
            printf("Windows Vista\n");
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
            printf("Windows 7\n");
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)
            printf("Windows 8\n");
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 3)
            printf("Windows 8.1\n");
        else if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0)
            printf("Windows 10\n");
    }
    if (is32Bit == TRUE)
        printf("32 bit\n");
    else
        printf("64 bit\n");
}

/* 
*   get cpu information
*   getCpuInfo() will show basic hardware information
*   getCpuUsage() acquire and calculate show cpu occupancy
*   referencing from: https://blog.csdn.net/u012234115/article/details/71056957
*/
DWORD deax;
DWORD debx;
DWORD decx;
DWORD dedx;

void initCpu(DWORD veax) {
	__asm
	{
		mov eax, veax
		cpuid
		mov deax, eax
		mov debx, ebx
		mov decx, ecx
		mov dedx, edx
	}
}

long getCpuFreq() {
	int start, over;
	_asm
	{
		RDTSC
		mov start, eax
	}

	Sleep(50);

	_asm
	{
		RDTSC
		mov over, eax
	}

	return (over - start) / 50000;
}

char* getManufactureID() {
	static char manuID[25];
	memset(manuID, 0, sizeof(manuID));

	initCpu(0);

	memcpy(manuID + 0, &debx, 4);  // copy to array
	memcpy(manuID + 4, &dedx, 4);
	memcpy(manuID + 8, &decx, 4);

	return manuID;
}

char* getCpuType() {
	DWORD id = 0x80000002;  // start 0x80000002 end to 0x80000004
	static char cpuType[49];
	memset(cpuType, 0, sizeof(cpuType));

	for (DWORD t = 0; t < 3; t++) {
		initCpu(id + t);
		memcpy(cpuType + 16 * t + 0, &deax, 4);
		memcpy(cpuType + 16 * t + 4, &debx, 4);
		memcpy(cpuType + 16 * t + 8, &decx, 4);
		memcpy(cpuType + 16 * t + 12, &dedx, 4);
	}

	return cpuType;
}

void getCpuInfo() {
	printf("CPU manufacture:\t%s\n", getManufactureID());
	printf("CPU type:\t%s\n", getCpuType());
	printf("CPU main freqency:\t%dMHz\n", getCpuFreq());
}

__int64 CompareFileTime(FILETIME time1, FILETIME time2) {
    __int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
    __int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;
    return (b - a);
}

void getCpuUsage()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);

    HANDLE hEvent;
    FILETIME pre_idleTime;
    FILETIME pre_kernelTime;
    FILETIME pre_userTime;

    pre_idleTime = idleTime;
    pre_kernelTime = kernelTime;
    pre_userTime = userTime;

    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    while (1) {
        WaitForSingleObject(hEvent, 1000);
        GetSystemTimes(&idleTime, &kernelTime, &userTime);

		int idle = CompareFileTime(pre_idleTime, idleTime);
		int kernel = CompareFileTime(pre_kernelTime, kernelTime);
		int user = CompareFileTime(pre_userTime, userTime);

		if(kernel + user == 0)
			printf("0.0\n");
		
		float ratio = abs((kernel + user - idle) * 100 / (kernel + user));
		printf("%.2f\n", ratio);
		
		pre_idleTime = idleTime;
		pre_kernelTime = kernelTime;
		pre_userTime = userTime;

    }
}

int main() {
    // getProcessInfo();
    // getIP();
    // getSysInfo();
    // getCpuInfo();
    // getCpuRatio();
    return 0;
}
