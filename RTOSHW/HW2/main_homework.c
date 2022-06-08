/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/*TICKSTOMS*/
#define pdTICKS_TO_MS( xTicks ) ( ( ( TickType_t ) ( xTicks ) * 1000U ) / configTICK_RATE_HZ )

/* Numero di task */
#define TASK_NUM 5

/* Periodo di Base */
#define BASE_PERIOD_MS 10

/*Priorità dei task*/
#define PRIORITY_RT (tskIDLE_PRIORITY + 3)
#define PRIORITY_ENCODER (tskIDLE_PRIORITY + 2)
#define PRIORITY_DIAGSCOPE (tskIDLE_PRIORITY + 1)

/* Definizione dei task da implementare */
static void encoder(void* pvParameters);
static void rt_1(void* pvParameters);
static void rt_2(void* pvParameters);
static void scope(void* pvParameters);
//static void diagnostic(void* pvParameters);

struct enc_str
{
	unsigned int slit;		//valori oscillanti tra 0 e 1
	unsigned int home_slit;	//1 se in home, 0 altrimenti
    SemaphoreHandle_t lock;
};

struct _rising_edge{
	unsigned int count;
	SemaphoreHandle_t lock;
};

struct _round_time{
	unsigned long int time_diff;
	SemaphoreHandle_t lock;
};

struct _slack_rt1{
	unsigned long int slack_time;
	SemaphoreHandle_t lock;
};

struct _slack_rt2{
	unsigned long int slack_time;
	SemaphoreHandle_t lock;
};

static struct enc_str enc_data;
static struct _rising_edge rising_edge;
static struct _round_time round_time;
static struct _slack_rt1 slack_rt1;
static struct _slack_rt2 slack_rt2;
static float periods[TASK_NUM];


void main_homework(void)
{
	
	/* Inizializzare i periodi dei task */
	periods[0]=periods[1]=BASE_PERIOD_MS; //periodo di scope e diagnostic
	periods[2]=(BASE_PERIOD_MS/100); //periodo di encoder
	periods[3]=periods[4]=(BASE_PERIOD_MS/200); //periodi dei task rt1 e rt2

	//creazione mutex
	enc_data.lock=xSemaphoreCreateMutex();
	rising_edge.lock=xSemaphoreCreateMutex();
	round_time.lock=xSemaphoreCreateMutex();
	slack_rt1.lock=xSemaphoreCreateMutex();
	slack_rt2.lock=xSemaphoreCreateMutex();

	//creazione task
	xTaskCreate(encoder,"Encoder",configMINIMAL_STACK_SIZE,NULL,PRIORITY_ENCODER,NULL);
	xTaskCreate(rt_1, "rt1", configMINIMAL_STACK_SIZE, NULL, PRIORITY_RT, NULL);
	xTaskCreate(rt_2,"rt2",configMINIMAL_STACK_SIZE,NULL,PRIORITY_RT,NULL);
	xTaskCreate(scope,"scope",configMINIMAL_STACK_SIZE,NULL,PRIORITY_DIAGSCOPE,NULL);
	//xTaskCreate(diagnostic,"diagnostic",configMINIMAL_STACK_SIZE,NULL,PRIORITY_DIAGSCOPE,NULL);

	//start scheduler
	vTaskStartScheduler();
	for (;; );
}

static void encoder(void* pvParameters)
{
	(void) pvParameters;

	printf("Encoder Start\n");
	
	xSemaphoreTake(enc_data.lock,portMAX_DELAY);
	enc_data.slit = 0;
	enc_data.home_slit = 0;
	xSemaphoreGive(enc_data.lock);

	unsigned int count = 0;
	unsigned int slit_count = 0;
	unsigned int prev_slit = 0;

	/* Randomized period (75-750 RPM) */
	srand(time(NULL));
	unsigned int semi_per = (rand() % 10) + 1;
	printf("[ENCODER] genero semiper %d", semi_per);
	
	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = pdMS_TO_TICKS(periods[2]);
	xNextWakeTime = xTaskGetTickCount();

	for( ;; ) {
	vTaskDelayUntil(&xNextWakeTime, xBlockTime );
	
	xSemaphoreTake(enc_data.lock,portMAX_DELAY);
	
		prev_slit = enc_data.slit;
		if (count%semi_per == 0) {
			enc_data.slit++;
			enc_data.slit%=2;
		}

		if (prev_slit==0&&enc_data.slit==1) 					//fronte di salita
			slit_count=(++slit_count)%8;

		if (slit_count==0) enc_data.home_slit=enc_data.slit;
		else enc_data.home_slit=0;
		
		count++;

	xSemaphoreGive(enc_data.lock);
	}
}


static void rt_1(void* pvParameters){
	
	(void) pvParameters;

	printf("rt1 Start\n");

	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = pdMS_TO_TICKS(periods[3]);
	xNextWakeTime = xTaskGetTickCount();

	xSemaphoreTake(rising_edge.lock,portMAX_DELAY);
	rising_edge.count=0;
	xSemaphoreGive(rising_edge.lock);

	int last_value=0;

	for(;;){
		vTaskDelayUntil(&xNextWakeTime, xBlockTime );
		xSemaphoreTake(enc_data.lock,portMAX_DELAY);
			if( last_value == 0 && enc_data.slit == 1){
				last_value = 1;
				xSemaphoreTake(rising_edge.lock,portMAX_DELAY);
				rising_edge.count++;
				xSemaphoreGive(rising_edge.lock);
			}
			else if(last_value == 1 && enc_data.slit == 0){
				last_value = 0;
			}
		xSemaphoreGive(enc_data.lock);
	}
}


static void rt_2(void* pvParameters){

	(void) pvParameters;

	printf("rt2 Start\n");

	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = pdMS_TO_TICKS(periods[4]);
	xNextWakeTime = xTaskGetTickCount();

	TickType_t time_home;
	TickType_t last_time_home;

	int first_measure=1;
	int last_home_slit=0;

	for(;;){
		vTaskDelayUntil(&xNextWakeTime, xBlockTime );

		xSemaphoreTake(enc_data.lock,portMAX_DELAY);
		
			if(enc_data.home_slit == 1 && last_home_slit == 0){
				last_home_slit = 1;
				if(first_measure){
					last_time_home=xTaskGetTickCount();
					first_measure = 0;
				}
				else{	
					time_home=xTaskGetTickCount();
					xSemaphoreTake(round_time.lock,portMAX_DELAY);
					round_time.time_diff = time_home - last_time_home;
					xSemaphoreGive(round_time.lock);
					last_time_home = time_home;	
				}
			}
			else if(enc_data.home_slit == 0){
				last_home_slit = 0;
			}
		xSemaphoreGive(enc_data.lock);
	}
}


static void scope(void* pvParameters){

	(void) pvParameters;

	printf("scope Start\n");

	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = pdMS_TO_TICKS(periods[0]);
	xNextWakeTime = xTaskGetTickCount();

	unsigned int count=0;
	float diff_us = 0;
	unsigned int rpm = 0;

	for(;;){
	vTaskDelayUntil(&xNextWakeTime, xBlockTime );

	xSemaphoreTake(rising_edge.lock,portMAX_DELAY);
	count = rising_edge.count;
	xSemaphoreGive(rising_edge.lock);

	printf("Rising Edge Counter : %d\t",count);

	xSemaphoreTake(round_time.lock,portMAX_DELAY);
	diff_us = (float)(round_time.time_diff / 1000);			//difference in microseconds
	xSemaphoreGive(round_time.lock);

	rpm = (unsigned int)(60*1000000/diff_us);
	printf("RPM : %u\n",rpm);	

	}
}

/*static void diagnostic(void* pvParameters) {
		
	(void) pvParameters;

	printf("diag Start\n");


	TickType_t xNextWakeTime;
	const TickType_t xBlockTime = pdMS_TO_TICKS(periods[1]);
	xNextWakeTime = xTaskGetTickCount();
    
	unsigned long int avg_slack=0;
	int i = 0;
	int rounds = 100;

	for(;;){
		vTaskDelayUntil(&xNextWakeTime, xBlockTime );
		
		xSemaphoreTake(slack_rt1.lock,portMAX_DELAY);
		xSemaphoreTake(slack_rt2.lock,portMAX_DELAY);

		avg_slack += (slack_rt1.slack_time + slack_rt2.slack_time)/2000; 	//average in microseconds

		xSemaphoreGive(slack_rt2.lock);
		xSemaphoreGive(slack_rt1.lock);
		
		i++;
		if(i == rounds){
			avg_slack = avg_slack/rounds;
			printf("**********SLACK TIME: %ld us**********\n",avg_slack);
			i = 0;
		}
	}
}*/
