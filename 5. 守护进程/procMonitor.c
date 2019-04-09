#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}\
while(0);\

struct myProcInfo
{
	char user[128];
	char cmd[128];
	char start_time[128];
	char etime[128];	// means elapsed time or end time
	int state;	// if process exists, state = 1, otherwise, state = 0
	int vis;	// to mark this slot is empty or not
} procInfo[10000];

void create_deamon();
void parse(FILE *, char *, int *, int *);
int find(int, int *, int);

int main()
{
	FILE *fp;
	int fd;
	struct tm *t;
	time_t tt;
	char buf[1024];
	static int running_proc_pid[10000];
	static int running_proc_cnt;
	memset(procInfo, 0, sizeof(procInfo));
	create_deamon();
	while(1)
	{
		// using popen() to relocate output stream
		// using 'ps -eo' shell order to acquire necessary information
		fp = popen("ps -eo pid,user,start_time,etime,comm", "r");

		// open log file
		fd = open("home/rwong/Documents/procMonitor/procInfo.log", O_WRONLY | O_CREAT | O_APPEND , 0644);
		// to clear content of procInfo.log
		ftruncate(fd, 0);
		lseek(fd, 0, SEEK_SET);
		
		memset(buf, 0, sizeof(buf));
		memset(running_proc_pid, 0, sizeof(running_proc_pid));
		running_proc_cnt = 0;
		// record process information
		parse(fp, buf, running_proc_pid, &running_proc_cnt);
		char c[10];
		sprintf(c, "cnt:%d\n", running_proc_cnt);

		// visit processInfo to check if there were process has been terminated
		sprintf(buf, "%4s%10s%30s%12s%12s\n", "pid", "user", "name", "start_time", "end_time");
		write(fd, buf, strlen(buf));

		char end_time[12];
		time(&tt);
		t = localtime(&tt);
		sprintf(end_time, "%02d:%02d", t->tm_hour, t->tm_min);
		for(int pid = 0; pid < 10000 ; pid++)
		{
			if(procInfo[pid].vis == 0)
				continue;
			// if the process doesn't exists
			// change its state in procInfo and record current time
			// and record it to log file

			// change at Apr 10 00:35
			// haven't been tested
			// maybe some bug here
			if((find(pid, running_proc_pid, running_proc_cnt) == -1) && procInfo[pid].state == 1)
			{
				procInfo[pid].state = 0;
				strcpy(procInfo[pid].etime, end_time);
			}
			if(procInfo[pid].state == 1)
				sprintf("--:--", procInfo[pid].etime);
			sprintf(buf, "%4d%10s%30s%12s%12s\n",
						pid,
						procInfo[pid].user,
						procInfo[pid].cmd,
						procInfo[pid].start_time,
						procInfo[pid].etime;
			write(fd, buf, strlen(buf));
		}
		
		close(fd);
		pclose(fp);

		sleep(10);
	}
	return 0;
}

void create_deamon()
{
	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork error");
	if(pid > 0)
		exit(EXIT_SUCCESS);
	if(setsid() == -1)
		ERR_EXIT("setsid error");
	chdir("/");
	umask(0);
	for(int i = 0; i < 65535; i++)
		close(i);
	return;
}

void parse(FILE *fp, char *src, int *pids, int *cnt)
{
	char tmp[1024];
	int start;
	int len;
	int pid;
	// read the tool tip on line 1
	fgets(src, 1024, fp);
	while(fgets(src, 1024, fp) != NULL)
	{
		strcpy(tmp, src);
	
		start = 0;
		len = 0;
	
		/* read pid info */
		pid = 0;
		while(src[len] == ' ')
			++len;
		start = len;
		while(src[len] != ' ')
		{
			pid = 10 * pid + src[len] - '0';
			++len;
		}

		// record the pid
		pids[(*cnt)] = pid;
		++(*cnt);
		// if this process has been recorded, then continue
		if(procInfo[pid].vis == 1)
			continue;
		// else, record this process
		procInfo[pid].vis = 1;
		// set process state 
		procInfo[pid].state = 1;

		/* read user info */
		while(src[len] == ' ')
			++len;
		start = len;
		while(src[len] != ' ')
			++len;
		tmp[len] ='\0';
		strcpy(procInfo[pid].user, tmp + start);

		/* read start_time info */
		while(src[len] == ' ')
			++len;
		start = len;
		while(src[len] != ' ')
			++len;
		tmp[len] = '\0';
		strcpy(procInfo[pid].start_time, tmp + start);

		/* read elapsed time info */
		while(src[len] == ' ')
			++len;
		start = len;
		while(src[len] != ' ')
			++len;
		tmp[len] = '\0';
		strcpy(procInfo[pid].etime, tmp + start);

		/* read cmd info */
		while(src[len] == ' ')
			++len;
		start = len;
		while(src[len] != '\n' && src[len] != '\0')
			++len;
		tmp[len] = '\0';
		strcpy(procInfo[pid].cmd, tmp + start);
	}
}

int find(int x, int *arr, int n)
{
	for(int i = 0; i < n; i++)
		if(arr[i] == x)
			return i;
	return -1;
}
