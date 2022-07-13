#include "main.h"

extern struct periodic_info tx_prf_periodic_info;

int Tx_Thread(void *param){
    
    printf("Tx_Thread created\n");
    double prf = *(double *)param; // kHz prf
    int period = round(1/prf); // msec period

    // initialize once when thead created
    printf("period %d\n", period);

    make_periodic(1000 * period, &tx_prf_periodic_info); 

    // Thread Loop
    while(1){        
        // tx start seqeunece
        printf("tx start\n");
        

        sem_post(&sem_daq); //tx동작 끝나면 daq쓰레드 깨워서 data acquisition시작

        // PRF 
        wait_period(&tx_prf_periodic_info);

        printf("tx done\n");
    }

    return 0;
}
