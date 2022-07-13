#include "main.h"

// test
extern struct status_info info;

int Motor_Thread(){
    // initialize once when thead created
    printf("MOTOR_Thread Created\n");

    // Thread Loop
    while(1){
        // wait semaphore. sem_wait(), sem_post() 사이 : critical section 
        sem_wait(&sem_mt_start);

        printf("motor control start with info\n");

        // motor moving time
        sleep(info.mt_time);

        // motor done
        printf("motor done\n");
        sem_post(&sem_mt_done);

    }

    return 0;
}
