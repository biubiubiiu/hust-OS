#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 60

// 获得当前时间，并写入数组 buffer 中
// 格式化为yy-mm-dd 格式
// 会在月份/日期前补 0 
void getTime(char *buffer) {
	time_t t;
	struct tm *lt;
	time(&t);
	lt = localtime(&t);
	sprintf(buffer, "%d%s%d%s%d\n", lt->tm_year + 1900, lt->tm_mon + 1 < 10?"0":"", lt->tm_mon + 1, lt->tm_mday < 10? "0":"", lt->tm_mday);
}

int main()
{
	FILE *stream;
	char cmdLine[MAX_LEN];
	char TimeBuffer[MAX_LEN];

	// 创建进程所需参数
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	// 打开本地文件
	stream = fopen("command.txt", "r+");
	// 若打开失败，则退出程序
	if (stream == NULL) {
		exit(0);
	}
	
	// 写入当前日期到 TimeBuffer 中
	getTime(TimeBuffer);
	// 将 TimeBuffer 内容写入文件
	fprintf(stream, "%s", TimeBuffer);
	// 移动文件指针到有效位置
	int len = strlen(TimeBuffer);
	fseek(stream, len, SEEK_SET);
	fscanf(stream, "\n");

	// 读取可执行程序名称
	while (fgets(cmdLine, MAX_LEN, stream) != NULL) {
		// fgets 会读入不必要的换行符
		// 带有换行符的命令行将无法正确执行（也许与版本有关）
		// 此处进行换行符的检测和替换
		int p = 0;
		while (cmdLine[p] != '\0' && cmdLine[p] != '\n')
			++p;
		if (cmdLine[p] == '\n')
			cmdLine[p] = '\0';
		// 创建进程
		CreateProcess(NULL,
			cmdLine,
			NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL,
			&si,
			&pi);
	}

	// 关闭文件流
	fclose(stream);

	return 0;
}
