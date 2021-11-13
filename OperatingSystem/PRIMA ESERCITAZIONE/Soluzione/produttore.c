/* PROCESSO PRODUTTORE */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


int main(){
	srand(getpid()*time(NULL));
	//mi prendo soltanto i semafori e la memoria condivisa quindi 0
	key_t keyshm =ftok("./" , 'a');
	int shm_ds = shmget(keyshm , 0 , IPC_CREAT | 0664 );
	key_t keysem = ftok("./", 'm');
	int sem_ds = semget(keysem ,0, IPC_CREAT| 0664);
	
	BufferCircolare * b= (BufferCircolare*) shmat(shm_ds,0,0);
	produci_elemento(sem_ds,b);
	return 1;
}
