/*
    main control thread
*/
#include "main.h"

// global parameters
struct periodic_info
{
	int timer_fd;
	unsigned long long wakeups_missed;
};

struct periodic_info rx_periodic_info;

// thread & functions
extern int GAGE_Thread();
extern int DAQ_Thread();

static int WatchDog_Thread();
static uint64_t get_posix_clock_time_usec();
static int make_periodic(unsigned int period, struct periodic_info *info);
static void wait_period (struct periodic_info *info);

int mq_initialize();
int thread_initialize();

int main(int argc, char **argv){
    
    int cmd = 0;

    //initialize & create message queue
    mq_initialize();

    // initialize & create thread
    thread_initialize();

    while(1){
        mq_receive(watchdog_mq, &cmd, sizeof(cmd), NULL);

        switch(cmd){
            case 0:
                printf("DAQ start\n");
                cmd = 0;
                mq_send(daq_mq, &cmd, sizeof(cmd), NULL);
            break;
        }

    }

    return 0;
}

int WatchDog_Thread(){

    int cmd = 0;
    uint64_t time1, time2, time_diff;

    time1 = get_posix_clock_time_usec();
    make_periodic(1000*10, &rx_periodic_info); // 10ms timer 

    while(1){
        wait_period(&rx_periodic_info);
        time2 = time1;
		time1 = get_posix_clock_time_usec();
        time_diff = time1 - time2;

        printf("watchdog thread periodic wakeup after: %lf ms\n", (double)time_diff/ 1000);

        // monitoring GAGE card state


        // if GAGE ready
        cmd = 0;
        mq_send(watchdog_mq, &cmd, sizeof(cmd), NULL);
    }

    return 0;
}

int mq_initialize(){

    struct mq_attr attr;
    attr.mq_maxmsg = 20; // maximum # of messages on queue
    attr.mq_msgsize = sizeof(int); // message size = sizeof

    daq_mq  = mq_open("/daq_mq", O_RDWR|O_CREAT, 0666, &attr);
    if(daq_mq == -1){
        printf("daq_mq open error\n");
        exit(-1);
    }

    gage_mq = mq_open("/gage_mq", O_RDWR|O_CREAT, 0666, &attr);
    if(gage_mq == -1){
        printf("gage_mq open error\n");
        exit(-1);
    }

    daehyun_mq = mq_open("/daehyun_mq", O_RDWR|O_CREAT, 0666, &attr);
    if(daehyun_mq == -1){
        printf("daehyun_mq open error\n");
        exit(-1);
    }


    return 0;
}

int thread_initialize(){

    pthread_t gage_thread, daq_thread, watchdog_thread;

    pthread_create(&gage_thread, NULL, GAGE_Thread, NULL);
    pthread_detach(gage_thread);

    pthread_create(&daq_thread, NULL, DAQ_Thread, NULL);
    pthread_detach(daq_thread);

    pthread_create(&watchdog_thread, NULL, WatchDog_Thread, NULL);
    pthread_detach(watchdog_thread);

    return 0;
}

uint64_t get_posix_clock_time_usec()
{
    struct timespec ts;

    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0)
        return (uint64_t) (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
    else
        return 0;
}

int make_periodic(unsigned int period, struct periodic_info *info)
{
	int ret;
	unsigned int ns;
	unsigned int sec;
	int fd;
	struct itimerspec itval;

	/* Create the timer */
	fd = timerfd_create (CLOCK_MONOTONIC, 0);
	info->wakeups_missed = 0;
	info->timer_fd = fd;
	if (fd == -1)
		return fd;

	/* Make the timer periodic */
	sec = period/1000000;
	ns = (period - (sec * 1000000)) * 1000;
	itval.it_interval.tv_sec = sec;
	itval.it_interval.tv_nsec = ns;
	itval.it_value.tv_sec = sec;
	itval.it_value.tv_nsec = ns;
	ret = timerfd_settime (fd, 0, &itval, NULL);
	return ret;
}

void wait_period (struct periodic_info *info)
{
	unsigned long long missed;
	int ret;

	/* Wait for the next timer event. If we have missed any the
	   number is written to "missed" */
	ret = read (info->timer_fd, &missed, sizeof (missed));
	if (ret == -1)
	{
		perror ("read timer");
		return;
	}

	/* "missed" should always be >= 1, but just to be sure, check it is not 0 anyway */
	if (missed > 0)
		info->wakeups_missed += (missed - 1);
}