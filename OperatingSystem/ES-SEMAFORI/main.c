#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

#include "processi.h"

int main()
{

    int vett_id;
    int buffer_id;
    int sem_id;
    int *vettore;
    int *buffer;

    key_t  chiavevett =ftok("./",'a');
    vett_id = shmget(chiavevett,sizeof(int)*NUM_ELEMENTI,IPC_CREAT|0664);

    if (vett_id < 0){
        perror("Impossibile creare l'array di interi condiviso");
        exit(1);
    }

    vettore = (int*)shmat(vett_id,0,NULL);

    if (vettore == (void *)-1){
        perror("Impossibile inizializzare l'array di interi condiviso");
        _exit(1);
    }

    srand((int)"matteo"*time(NULL)); 
    for (int i = 0; i < NUM_ELEMENTI; i++)
    {
        vettore[i] = rand() % INT_MAX;
    }

    key_t chiavebuffer = ftok("./",'b');
    buffer_id = shmget(chiavebuffer,sizeof(int),IPC_CREAT|0664);

    if (buffer_id < 0){
        perror("Impossibile creare il buffer condiviso");
        _exit(1);
    }

    buffer = (int*)shmat(buffer_id,0,NULL);

    if (buffer == (void *)-1){
        perror("Impossibile inizializzare il buffer condiviso");
        _exit(1);
    }

    *buffer = INT_MAX;

    sem_id = inizializza_semafori();

    for(int i=0; i<NUM_PROCESSI; i++){
        int pid=fork();
        if (pid==0){
            figlio(vettore,buffer,sem_id,i*ELEM_PER_FIGLIO,ELEM_PER_FIGLIO);
            _exit(0);
        }
    }

    padre(buffer, sem_id);

    semctl(sem_id, 0, IPC_RMID);
    shmctl(vett_id, IPC_RMID, 0);
    shmctl(buffer_id, IPC_RMID, 0);
}

