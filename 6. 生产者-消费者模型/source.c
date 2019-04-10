#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

CRITICAL_SECTION cs; // 定义互斥量对象
HANDLE empty;        // 缓冲区中空位的个数
HANDLE full;         // 缓冲区中数据的个数

int buffer[10] = {0}; // 使用整型数组模拟缓冲区
int pos = -1;         // 记录buffer最后一个元素的下标
char buf[30];         // 用于输出提示信息

DWORD WINAPI producer(LPVOID lpParam)
{
    int id = *(int *)lpParam; // 获得生产者的id号

    for (int k = 0; k < 15; k++)
    {
        WaitForSingleObject(empty, INFINITE); // P(empty)
        EnterCriticalSection(&cs);            // 进入临界区

        FILE *fp = fopen(".//info.txt", "a+");
        srand((unsigned)time(NULL));
        int newItem = 1000 * id + rand() % 1000; // 生产者i产生的数据范围为:1000*i ~ 1000*(i+1)
        sprintf(buf, "Producer %d: add %d to buffer\n", id, newItem);
        printf("%s", buf);
        fprintf(fp, "%s", buf);  // 向文件写入信息
        buffer[++pos] = newItem; // 向buffer中添加数据
        fclose(fp);

        LeaveCriticalSection(&cs);       // 退出临界区
        ReleaseSemaphore(full, 1, NULL); // V(full)

        int waitTime = rand() % 900 + 100; // 睡眠100ms ~ 1s
        Sleep(waitTime);
    }

    return 0;
}

DWORD WINAPI consumer(LPVOID lpParam)
{
    int id = *(int *)lpParam; // 获得消费者的id号

    for (int k = 0; k < 10; k++)
    {
        WaitForSingleObject(full, INFINITE); // P(full)
        EnterCriticalSection(&cs);           // 进入临界区

        FILE *fp = fopen(".//info.txt", "a+");
        sprintf(buf, "Consumer %d: remove %d from buffer\n", id, buffer[pos]);
        buffer[pos--] = 0; // 从buffer中移除数据
        printf("%s", buf);
        fprintf(fp, "%s", buf); // 向文件写入信息
        fclose(fp);

        LeaveCriticalSection(&cs);        // 退出临界区
        ReleaseSemaphore(empty, 1, NULL); // V(empty)

        srand((unsigned)time(NULL));
        int waitTime = rand() % 900 + 100; // 睡眠100ms ~ 1s
        Sleep(waitTime);
    }

    return 0;
}

int main()
{
    // 使用信号量进行同步
    full = CreateSemaphore(NULL, 0, 10, "full");
    empty = CreateSemaphore(NULL, 10, 10, "empty");
    // 使用临界区进行互斥
    InitializeCriticalSection(&cs);

    // 先清空一下文件
    FILE *fp = fopen(".//info.txt", "w+");
    fclose(fp);

    // 创建2个生产者，3个消费者
    HANDLE hThread[5];
    int id[3] = {1, 2, 3};
    hThread[0] = CreateThread(NULL, 0, producer, (void *)&id[0], 0, NULL);
    hThread[1] = CreateThread(NULL, 0, producer, (void *)&id[1], 0, NULL);
    hThread[2] = CreateThread(NULL, 0, consumer, (void *)&id[0], 0, NULL);
    hThread[3] = CreateThread(NULL, 0, consumer, (void *)&id[1], 0, NULL);
    hThread[4] = CreateThread(NULL, 0, consumer, (void *)&id[2], 0, NULL);
    WaitForMultipleObjects(5, hThread, TRUE, INFINITE);

    // 输出缓冲区内容
    printf("buffer state:\n");
    for (int i = 0; i < 10; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    CloseHandle(full);
    CloseHandle(empty);
    DeleteCriticalSection(&cs);

    getchar();
    return 0;
}
