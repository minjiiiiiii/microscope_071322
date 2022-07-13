#include <stdio.h>  
#include <stdint.h>     // uint
#include <fcntl.h>      // O_RWWR flag
#include <pthread.h>    // thread
#include <semaphore.h>  // semaphore
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "CsTypes.h"
#include "CsPrototypes.h"
#include "CsAppSupport.h"
#include "CsTchar.h"
#include "CsSdkMisc.h"


// command define
#define INIT    0
#define START   1
#define STOP    2

sem_t sem_main;  // main semaphore
sem_t sem_daq;       // daq semaphore
sem_t sem_tx;        // tx semaphore
sem_t sem_mt_start, sem_mt_done;     // motor semaphore
sem_t sem_watchdog;  // watchdog semaphore

pthread_t daq_thread, tx_thread, motor_thread, watchdog_thread;

struct status_info
{
    // device status
    int gage_ready;
    int motor_ready;
    int motor_done;


    // parameters
    double prf; // Tx prf
    int num_frame;


    // test parameter
    int mt_time;

};

struct periodic_info
{
	int timer_fd;
	unsigned long long wakeups_missed;
};

// make periodic wakeup
uint64_t get_posix_clock_time_usec();
int make_periodic(unsigned int period, struct periodic_info *info);
void wait_period (struct periodic_info *info);

