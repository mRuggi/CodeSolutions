/*PROCESSO CONSUMATORE*/

#include <stdio.h> //standard i/o
#include <sys/ipc.h> //flag ipc
#include <sys/types.h> //tipi key_t e pid_t
#include <sys/sem.h> //semafori
#include <sys/shm.h> //memorie condivise
#include <sys/wait.h> //wait
#include <unistd.h> //fork e exec
#include <stdlib.h> //libreria standard
#include "header.h" //variabili globali


int main(){

	key_t keyshm =ftok("./" , 'a');
	int shm_ds = shmget(keyshm , 0 , IPC_CREAT | 0664 );
	key_t keysem = ftok("./", 'm');
	int sem_ds = semget(keysem ,0, IPC_CREAT| 0664);
	
	BufferCircolare * b= (BufferCircolare*) shmat(shm_ds,0,0);
	for(int i = 0; i<2; i++){
		consuma_elementi(sem_ds,b);
		sleep(2);
	}

	return 1;
}
