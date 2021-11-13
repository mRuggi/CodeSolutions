			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#define N 5

#define MUTEX_P 0
#define MSG_DISP 1
#define SPZ_DISP 2


typedef struct{
	int elementi[N];
	int testa;
	int coda;
} BufferCircolare;


void Wait_Sem(int id_sem, int numsem, int numop);
void Signal_Sem (int id_sem, int numsem, int numop);

void produci_elemento(int semid,BufferCircolare* buf);
void consuma_elementi(int semid, BufferCircolare* buf);

#endif
