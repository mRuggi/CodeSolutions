#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>
#include "parameters.h"

int main(int argc, char ** argv)
{
   
    //Apre coda per la richiesta e per la risposta
    mqd_t req_qd;
    if ((req_qd=mq_open(REQDS_QUEUE_NAME,O_WRONLY))==-1) {
        perror("diagWCET mqopen req_qd");
        return -1;
    }

    mqd_t res_qd;
    if ((res_qd=mq_open(ANSWRDS_QUEUE_NAME,O_RDONLY))==-1) {
        perror("diagWCET mqopen res_qd");
        return -1;
    }

    printf("[DiagWCET] started - sending WCETdiagnostic request\n");
    //manda la richiesta
    if(mq_send(req_qd,WCETREQ,WCETREQSIZE,WCETREQSIZE)==-1) {
        perror("diagWCET send WCET request error");
        return -1;
    }
    //ricevi la risposta
    char message [MAX_MSG_SIZE];

    printf("DIAGWCET in format ACQFILTERWCET-CONTROLWCET-ACTUATORWCET (all in seconds)\n");

    for(int i=0; i<3; i++){
        if (mq_receive(res_qd,message,MAX_MSG_SIZE,NULL) == -1){
                //printf ("No answer ...\n");							//DEBUG
        }else{
                printf(message);
        }
    }
    printf("\n");
    
    //clear (chiusura descrittori code)

     if (mq_close (req_qd) == -1) {
        perror ("diagWCET: mq_close req_qd");
        return -1;
    }

     if (mq_close (res_qd) == -1) {
        perror ("diagWCET: mq_close res_qd");
        return -1;
    }

    return 0;
}