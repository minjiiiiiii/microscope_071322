#include "main.h"

#include <time.h>

int DAQ_Thread(){
    // initialize once when thead created
    printf("DAQ_Thread Created\n");


    // Thread Loop
    while(1){
        // wait gage thread data acquisition
        sem_wait(&sem_daq);
        //printf("copy gage card databuffer\n");
        //daq start, save data
    
    
    }
}


