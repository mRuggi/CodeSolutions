#define TICK_TIME 100000
#define SENSOR_QUEUE_NAME   "/sensor_queue"
#define ACTUATOR_QUEUE_NAME "/actuator_queue"
#define REFERENCE_QUEUE_NAME "/reference_queue"
#define WDOG_QUEUE_NAME "/watchdog_queue"
#define REQDS_QUEUE_NAME "/req_ds"
#define ANSWRDS_QUEUE_NAME "/res_ds"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 1000
#define MAX_MSG_SIZE 16
#define BUF_SIZE 5
#define DIAGREQPRIO 0 //low
#define DIAGREQ "diag"
#define DIAGREQSIZE 5
#define WCETREQPRIO 1 //basta che sia maggiore di DIAGREQPRIO
#define WCETREQ "wcet"
#define WCETREQSIZE 5