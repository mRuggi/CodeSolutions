#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "header.h"

#define N_PROC 11


int main(){
	pid_t pid_ex,pid;
	int st,i;

	key_t keyshm =ftok("./" , 'a');
	int shm_ds = shmget(keyshm , sizeof(BufferCircolare) , IPC_CREAT | 0664 );

	key_t keysem = ftok("./", 'm');
	int sem_ds = semget(keysem ,3, IPC_CREAT| 0664);

	semctl(sem_ds,MUTEX_P,SETVAL,1);
	semctl(sem_ds,MSG_DISP,SETVAL,0);
	semctl(sem_ds,SPZ_DISP,SETVAL,N);
	
	//Istanziamo 
	for(i = 0; i < N_PROC;i++){
		pid = fork();
		if(pid == 0){
			if(i == 0){ //solo il primo è un consumatore
			execl("./consumatore","./consumatore",NULL);
			}else{ //gli altri 10 sono produttori
			execl("./produttore","./produttore",NULL);
			}
			_exit(0);			
		}
		sleep(1+rand()%3);
	}
	
	for(i = 0; i < N_PROC ; i++){
		pid_ex = wait(&st);
		printf("[MASTER] - Il processo %d ha terminato l'esecuzione\n",pid_ex);			
	}

	shmctl(shm_ds,IPC_RMID,0);
	semctl(sem_ds,0,IPC_RMID);

	return 0;
}
