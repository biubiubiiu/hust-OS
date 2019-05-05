#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define MAXLEN 1024

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

static int g_sum = 0;
static char buf[MAXLEN];

// the address which sent from sival_ptr is not the same between both processes
// thus I use pipe here to send string with signal to inform child process
// and use signal to send integar
int fd[2], nbytes;
int *write_fd = &fd[1];
int *read_fd = &fd[0];

void handler(int signum, siginfo_t *siginfo, void *context)
{
	// SIGUSR1 represents receiving integer
	if (signum == SIGUSR1)
	{
		printf("Receive integer\n");
		g_sum += siginfo->si_value.sival_int; // retrieve integer from si_value
		printf("Input number: %d\tsum: %d\n", siginfo->si_value.sival_int, g_sum);
		if (g_sum > 100)
		{
			printf("My work done!\n");
			sleep(1);
			kill(getppid(), SIGINT); // end parent process
		}
	}
	// SIGUSR2 represents receving string
	else if (signum == SIGUSR2)
	{
		printf("Receive string\n");
		// read string from pipe
		read(*read_fd, buf, sizeof(buf));
		printf("child process received: %s\n", buf);
	}
	printf("\n");
}

int main()
{
	if (pipe(fd) == -1)
	{
		printf("Create pipe failed!\n");
		getchar();
		return -1;
	}

	struct sigaction act;
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	pid_t pid;
	pid = fork();

	// this part will be executed by child process
	if (pid == 0)
	{
		printf("child process pid: %d\n", getpid());
		close(*write_fd);
		while (1)
			sleep(1);
	}
	// this part will be executed by parent process
	else
	{
		close(*read_fd);

		union sigval val;
		static int numInput;

		while (1) {
			gets(buf);
			BOOL flag = TRUE;
			int k = 1;
			int tmp = 0;
			// check if it's valid integer
			for (size_t i = 0; i < strlen(buf); i++) {
				if (buf[i] >= '0' && buf[i] <= '9')
					tmp = tmp * 10 + buf[i] - '0';
				else if (buf[i] == '-' && i == 0)
					k = -1;
				else
				{
					flag = FALSE;
					break;
				}
			}
			tmp *= k;
			// if yes, send integer through signal
			if (flag == TRUE) {
				printf("Send SIGNAL_INT to process %d\n", getpid() + 1);
				val.sival_int = tmp;
				sigqueue(pid, SIGUSR1, val);
			}
			// else, sent string through pipe
			else {
				printf("Send string to child process\n");
				write(*write_fd, buf, strlen(buf));
				kill(getpid() + 1, SIGUSR2);
			}
			sleep(1);
		}
	}

	return 0;
}
