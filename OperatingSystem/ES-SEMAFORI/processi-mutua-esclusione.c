#include "processi.h"
#include "semafori.h"

#include <sys/wait.h>
#include <limits.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int inizializza_semafori(){
    key_t semkey=ftok("./",'c');
    int sem_id = semget(semkey,1,IPC_CREAT|0664);

    if (sem_id < 0){
        perror("Impossibile creare il semaforo per la mutua esclusione");
        exit(1);
    }

    semctl(sem_id,MUTEX,SETVAL,1);

    return sem_id;
}

void figlio(int *vettore,int *buffer,int sem_id,int elemento_iniziale,int qta_elementi)
{

    int minimo = INT_MAX;

    for (int i = elemento_iniziale; i < elemento_iniziale + qta_elementi; i++)
    {
        if (vettore[i] < minimo)
        {
            minimo = vettore[i];
        }
    }

    Wait_Sem(sem_id,MUTEX);
    printf("Figlio: Il minimo locale è %d\n", minimo);
    if (minimo < *buffer)
    {
        *buffer = minimo;
    }

    Signal_Sem(sem_id,MUTEX);
}


void padre(int *buffer,int sem_id)
{
    for(int i=0; i<NUM_PROCESSI; i++){
    wait(NULL);
    }
    printf("Padre: Il valore minimo assoluto è: %d\n", *buffer);

}
