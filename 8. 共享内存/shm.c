#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <semaphore.h>

#define MAXLEN 100

struct sharedStruct {
	int isEmpty;		// 记录内容区是否为空
	char text[MAXLEN];	// 存放内容
};

int main()
{
	sem_t sem;
	int shmid;
	void *shm;
	struct sharedStruct *share;

	sem_init(&sem, 0, 1);
	
	// allocates a shared memory segment
	shmid = shmget((key_t)2000, sizeof(struct sharedStruct), 0666|IPC_CREAT);
	if(shmid == -1) {
		exit(EXIT_FAILURE);
	}
	
	// attach the shared memory segment to the address space
	shm = shmat(shmid, 0, 0);
	if(shm == (void*)-1) {
		exit(EXIT_FAILURE);
	}

	share = (struct shareStruct *)shm;
	share->isEmpty	= 1;

	pid_t pid;
	pid = fork();
	
	// this part will be executed by the child process
	if(pid == 0) { 
		printf("Child process has been created\n");
		while(1) {
			if(share->isEmpty == 1) {
				sleep(1);
			}
			else {
				sem_wait(&sem);
				printf("child process read %s\n", share->text);
				strcpy(share->text, "");
				share->isEmpty = 1;
				sem_post(&sem);
			}
			if(strncmp(share->text, "end", 3) == 0) {
				printf("child process quit\n");
				break;
			}
		}
	}
	// this part will be executed by the parent process
	else {
		printf("Parent process is running\n");
		int num = 1;
		while(num <= 100) {
			if(share->isEmpty == 1) {
				sem_wait(&sem);
				printf("parent process wrote %d\n", num);
				sprintf(share->text, "%d", num++);
				share->isEmpty = 0;
				sem_post(&sem);
			}
			else
				sleep(1);
		}
		sleep(2);	// ensure the last number has been received
		sprintf(share->text, "end");
		share->isEmpty = 0;
	}
	
	// detach the shared memory segment from the addrss space
	shmdt(shm);
	return 0;
}
