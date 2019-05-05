#define _CRT_SECURE_NO_WARNINGS

#include "graphics.h"
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>

constexpr double PI = 3.1415926535;

constexpr int THINKING = 0;
constexpr int HOLDING_ONE = 1;
constexpr int HOLDING_TWO = 2;

bool bChopsticksOnTable[5];
int  philosopherState[5];

POINT philosopher[5] = { {480, 65}, {755, 210}, {700, 485}, {240, 490}, {200, 210} };
POINT chopsticksOnTable[5] = { {620, 165}, {710, 370}, {540, 485}, {370, 370}, {420, 165} };

IMAGE imgThinking;
IMAGE imgEating;

HANDLE hChopsticks[5];
HANDLE hThread[5];
HANDLE hPhilosopherCnt;
CRITICAL_SECTION cs;

FILE* fp;

void init()
{
	for (int i = 0; i < 5; ++i) {
		bChopsticksOnTable[i] = true;
		philosopherState[i] = THINKING;
		hChopsticks[i] = CreateSemaphore(NULL, 1, 1, NULL);
	}
	hPhilosopherCnt = CreateSemaphore(NULL, 4, 4, NULL);
	InitializeCriticalSection(&cs);

	fp = fopen(".//log.txt", "w+");

	initgraph(1080, 720);
	setbkcolor(WHITE);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	cleardevice();

	loadimage(&imgThinking, L"./think.jpg");
	loadimage(&imgEating, L"./eat.jpg");
}

void refresh()
{
	clearrectangle(0, 0, 1080, 720);

	circle(540, 360, 180);

	for (int i = 0; i < 5; ++i) {
		putimage(philosopher[i].x, philosopher[i].y, philosopherState[i] == HOLDING_TWO ? &imgEating : &imgThinking);
	}
	for (int i = 0; i < 5; ++i) {
		if (philosopherState[i] != THINKING) {
			setfillcolor(BLACK);
			int left = philosopher[i].x;
			int top = philosopher[i].y + 20;
			solidrectangle(left, top, left + 10, top + 100);
			if(philosopherState[i] == HOLDING_TWO)
				solidrectangle(left + 100, top, left + 110, top + 100);
		}
		if(bChopsticksOnTable[i]){
			setfillcolor(BLACK);
			int left = chopsticksOnTable[i].x;
			int top = chopsticksOnTable[i].y;
			solidrectangle(left, top , left + 10, top + 100);
		}
	}
}

DWORD WINAPI eat(LPVOID lpParam)
{
	int id = *(int*)lpParam;
	int right = (id + 4) % 5;
	int left = id;

	while (1) {
		// P(hPhiposopherCnt)
		WaitForSingleObject(hPhilosopherCnt, INFINITE);

		// 拿起右手边的筷子
		WaitForSingleObject(hChopsticks[right], INFINITE);
		EnterCriticalSection(&cs);
		bChopsticksOnTable[right] = false;
		philosopherState[id] = HOLDING_ONE;
		fprintf(fp, "%d take %d\n", id, right);
		refresh();
		Sleep(1000);
		LeaveCriticalSection(&cs);

		// 拿起左手边的筷子
		WaitForSingleObject(hChopsticks[left], INFINITE);
		EnterCriticalSection(&cs);
		bChopsticksOnTable[left] = false;
		philosopherState[id] = HOLDING_TWO;
		fprintf(fp, "%d take %d\n", id, left);
		refresh();
		Sleep(1000);
		LeaveCriticalSection(&cs);

		// 保持恰饭
		srand((unsigned)time(NULL));
		int waitTime = rand() % 400 + 1000;
		Sleep(waitTime);

		// 为了方便展示，将放下筷子与对应的释放信号量过程分成两步
		// 以便直观展示恰饭之后的状态
		// 放下筷子
		EnterCriticalSection(&cs);
		bChopsticksOnTable[left] = true;
		bChopsticksOnTable[right] = true;
		philosopherState[id] = THINKING;
		fprintf(fp, "%d drop\n", id);
		refresh();
		Sleep(1000);
		LeaveCriticalSection(&cs);

		// 释放信号量
		EnterCriticalSection(&cs);
		ReleaseSemaphore(hChopsticks[left], 1, NULL);
		ReleaseSemaphore(hChopsticks[right], 1, NULL);
		refresh();
		Sleep(1000);
		LeaveCriticalSection(&cs);

		// V(hPhilosopherCnt)
		ReleaseSemaphore(hPhilosopherCnt, 1, NULL);

		// 保持思考
		waitTime = rand() % 400 + 1000;
		Sleep(waitTime);
	}

	return 0;
}

void threadRace()
{
	int id[5] = { 0, 1, 2, 3, 4 };

	// 创建5个线程
	for (int i = 0; i < 5; ++i)
		hThread[i] = CreateThread(NULL, 0, eat, (void*)& id[i], 0, NULL);

	WaitForMultipleObjects(5, hThread, TRUE, INFINITE);
}

int main()
{
	init();
	refresh();

	Sleep(1000);
	threadRace();

	for (int i = 0; i < 5; ++i) {
		CloseHandle(hChopsticks[i]);
	}
	CloseHandle(hPhilosopherCnt);
	fclose(fp);

	_getch();
	closegraph();
	return 0;
}
