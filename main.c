/*
    main control thread
*/
#include "main.h"

// global parameters
struct status_info info; // status info structure

struct periodic_info tx_prf_periodic_info;
struct periodic_info watchdog_periodic_info;
struct periodic_info main_periodic_info;

// thread, semaphore initialize functions
int sem_initialize();
int thread_initialize();
int param_initialize();

//gage card initialization, parameters for gage card //header로?
int gage_initialize();
int32 i32Status = CS_SUCCESS; //CS_SUCCESS defined as 1(Successful operation)
uInt32 i;
TCHAR szFileName[MAX_PATH]; //define MAX_PATH 256
int64 i64StartOffset = 0;
void* pBuffer = NULL;
float* pVBuffer = NULL;
uInt32 u32Mode;
CSHANDLE hSystem = 0; //CSHANDLE: uint32 
IN_PARAMS_TRANSFERDATA InData = {0};
OUT_PARAMS_TRANSFERDATA OutData = {0};
CSSYSTEMINFO CsSysInfo = {0};
CSAPPLICATIONDATA CsAppData = {0};
LPCTSTR szIniFile = _T("Acquire.ini"); //_T: _UNICODE가 define 되어 있으면 L"문자열" 리턴 _UNICODE가 define 되어 있지 않으면 "문자열" 리턴
FileHeaderStruct stHeader = {0}; 
CSACQUISITIONCONFIG CsAcqCfg = {0};
CSCHANNELCONFIG CsChanCfg = {0};
uInt32 u32ChannelIndexIncrement;
ARRAY_BOARDINFO *pArrayBoardInfo=NULL;

int64 i64Padding = 64; //extra samples to capture to ensure we get what we ask for
int64 i64SavedLength;
int64 i64MaxLength;
int64 i64MinSA;
int64 i64Status = 0;

clock_t clock(void); 

// thread & functions
extern int DAQ_Thread();
extern int Motor_Thread();
extern int Tx_Thread();
static int WatchDog_Thread();

// decode command from status info
static int status_decoder();

int main(int argc, char **argv){
    
    int iter = 0;

    //initialize & create semaphore for daq, tx, motor start/done, watchdog
    sem_initialize(); 

    // initialize & create thread. tx를 제외한 thread에서 sem_wait
    thread_initialize();

    //initialize gage card 
    gage_initialize();

IDLE:

    printf("wait external start\n");

    // wait external start signal
    sem_wait(&sem_watchdog);

    // gage, motor, tx initialize
    param_initialize();

    while(1){
        // motor start
        info.mt_time = 10;
        sem_post(&sem_mt_start);

        pthread_create(&tx_thread, NULL, Tx_Thread, &info.prf);

        sem_wait(&sem_mt_done);

        pthread_cancel(tx_thread);

        iter++;

        printf("current iter %d/%d\n", iter, info.num_frame);

        if(iter == info.num_frame){
            iter = 0;
            goto IDLE;
        }

        // motor start
        info.mt_time = 2;
        sem_post(&sem_mt_start);
        sem_wait(&sem_mt_done);
           
    }

    

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

int WatchDog_Thread(){

    int test_input = 1;

    uint64_t time1, time2, time_diff;

    time1 = get_posix_clock_time_usec();

    printf("watchdog thread created\n");
    
    while(1){
        printf("WatchDog_Thread Started\n"); //for debugging

        wait_period(&watchdog_periodic_info);

        time2 = time1;
		time1 = get_posix_clock_time_usec();
        time_diff = time1 - time2;
        printf("watchdog thread periodic wakeup after: %lf ms\n", (double)time_diff/ 1000);
        printf("WatchDong_Thread Ended\n"); //for debugging

        // // TODO: monitoring device status
        // info.gage_ready = 1;
        // info.motor_ready = 1;

        // if(test_input == 1){
        //     sem_post(&sem_watchdog);
        //     test_input = 0;
        // }
       
    }

    return 0;
}

int sem_initialize(){

    sem_init(&sem_daq, 0, 0); //sem_init(sem_t *sem, int pshared, unsigned int value), *sem: semaphore 포인터, pshared 0이면 쓰레드끼리 공유, value: semaphore가 가지는 초기값
    sem_init(&sem_tx, 0, 0);
    sem_init(&sem_mt_start, 0, 0); sem_init(&sem_mt_done, 0, 0);
    sem_init(&sem_watchdog, 0, 1);

    return 0;
}

int thread_initialize(){

    pthread_create(&daq_thread, NULL, DAQ_Thread, NULL); 
    pthread_detach(daq_thread); //pthread_detach : 쓰레드 분리

    pthread_create(&motor_thread, NULL, Motor_Thread, NULL);
    pthread_detach(motor_thread);

    // watchdog timer setup
    make_periodic(1000*500, &watchdog_periodic_info); // 500ms timer 

    pthread_create(&watchdog_thread, NULL, WatchDog_Thread, NULL);
    pthread_detach(watchdog_thread);

    //pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
    //first parameter- thread : 쓰레드가 성공적으로 생성되었을 때의 쓰레드 식별자
    //attr : 쓰레드 특성 지정 NULL : 기본 쓰레드 특성 사용
    //start_routine : 분기시켜서 실행할 쓰레드 함수
    //arg : start_routine쓰레드 함수의 매개변수로 pass
    //성공시 0 리턴 

    return 0;
}

int param_initialize(){


    
    info.prf = 0.001;   // structure staus_info 
    info.num_frame = 3; //change to sample #s later.
    
}

int gage_initialize(){
    printf("Initialize gage card setting\n");
    //for execution time 
    double start,end;

    /*
    Initializes the CompuScope boards found in the system. If the
    system is not found a message with the error code will appear.
    Otherwise i32Status will contain the number of systems found.
    */
    
    //printf(_T("\n\ti32Status = 1 when succeeded\n"));
    //printf(_T("\n\ti32Status(CsInitialize): %d\n"),i32Status); 
    printf("*****************************************************\n");
    printf("Gage card initialization Started\n");
    i32Status = CsInitialize();
    if (0 == i32Status)
    {
    printf("\nNo CompuScope systems found\n");
    return (-1);
    }
    if (CS_FAILED(i32Status))
    {
    DisplayErrorString(i32Status);
    return (-1);
    }

    /*
    Get the system. This sample program only supports one system. If
    2 systems or more are found, the first system that is found
    will be the system that will be used. hSystem will hold a unique
    system identifier that is used when referencing the system.
    */
    i32Status = CsGetSystem(&hSystem, 0, 0, 0, 0);
    printf(_T("\n\ti32Status(CsGetSystem) : %d\n"),i32Status); 
    printf("*****************************************************\n");
    if (CS_FAILED(i32Status))
    {
    DisplayErrorString(i32Status);
    return (-1);
    }
    /*
    Get System information. The u32Size field must be filled in
    prior to calling CsGetSystemInfo
    */
    CsSysInfo.u32Size = sizeof(CSSYSTEMINFO);
    i32Status = CsGetSystemInfo(hSystem, &CsSysInfo);
    //printf(_T("\n\ti32Status(CsGetSystemInfo) : %d\n"),i32Status); 
    //printf(_T("\n\tsizeof(CSSYSTEMINFO) : %u\n"),CsSysInfo.u32Size); 
    //printf(_T("\n\tCsSysInfo.u32BoardCount : %u\n"),CsSysInfo.u32BoardCount); 
    //printf(_T("\n\tsizeof(CSBOARDINFO) : %lu\n"),sizeof(CSBOARDINFO));
    //printf(_T("\n\tsizeof(ARRAY_BOARDINFO) : %lu\n"),sizeof(ARRAY_BOARDINFO));
    //printf(_T("\n\tsizeof(CSSYSTEMINFO) : %lu\n"),sizeof(CSSYSTEMINFO));
    //printf("*****************************************************\n");

    pArrayBoardInfo = VirtualAlloc (NULL, ((CsSysInfo.u32BoardCount - 1) * sizeof(CSBOARDINFO)) + sizeof(ARRAY_BOARDINFO), MEM_COMMIT, PAGE_READWRITE);
    //VirtualAlloc LPVOID VirtualAlloc(LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect);
    //lpAddress : NULL이면 system이 알아서 번지 할당, dwSize :할당하고자 하는 메모리의 양(byte단위), flAllocationType :MEM_COMMIT 이면 물리적 메모리(RAM,하드디스크) 할당, flProtect: PAGE_READWRITE :엑세스 타입 
    //가상메모리 크기/페이지 하나 당 크기 = 페이지 개수 
    //printf(_T("\n\tCsAppData.i64TransferLength : %u"),(CsSysInfo.u32BoardCount - 1)); 
    //printf(_T("\n\tsizeof(CSBOARDINFO) : %lu"),sizeof(CSBOARDINFO)); 
    //printf(_T("\n\tsizeof(ARRAY_BOARDINFO) : %lu"),sizeof(ARRAY_BOARDINFO)); 
    //printf(_T("\n\tThe size of the allocated memory : %lu\n"),((CsSysInfo.u32BoardCount - 1) * sizeof(CSBOARDINFO)) + sizeof(ARRAY_BOARDINFO));
    //printf("*****************************************************\n");

    if (!pArrayBoardInfo)
    {
    printf (_T("\nUnable to allocate memory\n"));
    CsFreeSystem(hSystem);
    return (-1);
    }
    pArrayBoardInfo->u32BoardCount = CsSysInfo.u32BoardCount;
    for (i = 0; i < pArrayBoardInfo->u32BoardCount; i++)
    {
    pArrayBoardInfo->aBoardInfo[i].u32BoardIndex = i + 1;
    pArrayBoardInfo->aBoardInfo[i].u32Size = sizeof(CSBOARDINFO);
    }
    i32Status = CsGet(hSystem, CS_BOARD_INFO, CS_ACQUISITION_CONFIGURATION, pArrayBoardInfo);
    //printf(_T("\n\ti32Status(CsGet) : %d\n"),i32Status); 
    /*
    Display the system name from the driver
    */
    printf(_T("\nBoard Name: %s"), CsSysInfo.strBoardName);
    for (i = 0; i < pArrayBoardInfo->u32BoardCount; i++)
    {
    printf(_T("\n\tSerial[%d]: %s"), i, pArrayBoardInfo->aBoardInfo[i].strSerialNumber);
    }
    printf(_T("\n"));

    i32Status = CsAs_ConfigureSystem(hSystem, (int)CsSysInfo.u32ChannelCount, 1, (LPCTSTR)szIniFile, &u32Mode);
    //printf(_T("\n\ti32Status(CsAs_Configuration) : %d\n"),i32Status); 
    if (CS_FAILED(i32Status))
    {
    if (CS_INVALID_FILENAME == i32Status)
    {
    /*
    Display message but continue on using defaults.
    */
    printf(_T("\nCannot find %s - using default parameters."), szIniFile);
    }
    else
    {
    /*
    Otherwise the call failed. If the call did fail we should free the CompuScope
    system so it's available for another application
    */
    DisplayErrorString(i32Status);
    CsFreeSystem(hSystem);
    VirtualFree (pArrayBoardInfo, 0, MEM_RELEASE);
    return(-1);
    }
    }
    /*
    If the return value is greater than 1, then either the application,
    acquisition, some of the Channel and / or some of the Trigger sections
    were missing from the ini file and the default parameters were used.
    */
    if (CS_USING_DEFAULT_ACQ_DATA & i32Status)
    printf(_T("\nNo ini entry for acquisition. Using defaults."));
    if (CS_USING_DEFAULT_CHANNEL_DATA & i32Status)
    printf(_T("\nNo ini entry for one or more Channels. Using defaults for missing items."));

    if (CS_USING_DEFAULT_TRIGGER_DATA & i32Status)
    printf(_T("\nNo ini entry for one or more Triggers. Using defaults for missing items."));

    i32Status = CsAs_LoadConfiguration(hSystem, szIniFile, APPLICATION_DATA, &CsAppData);
    //printf(_T("\n\ti32Status(CsAs_LoadConfiguration) : %d\n"),i32Status); 
    printf("Gage card configuration succeeded\n");
    if (CS_FAILED(i32Status))
    {
    if (CS_INVALID_FILENAME == i32Status)
    {
    printf(_T("\nUsing default application parameters."));
    }
    else
    {
    DisplayErrorString(i32Status);
    CsFreeSystem(hSystem);
    VirtualFree (pArrayBoardInfo, 0, MEM_RELEASE);
    return -1;
    }
    }
    else if (CS_USING_DEFAULT_APP_DATA & i32Status)
    {
    /*
    If the return value is CS_USING_DEFAULT_APP_DATA (defined in ConfigSystem.h)
    then there was no entry in the ini file for Application and we will use
    the application default values, which have already been set.
    */
    printf(_T("\nNo ini entry for application data. Using defaults."));
    }

    /*
    Commit the values to the driver. This is where the values get sent to the
    hardware. Any invalid parameters will be caught here and an error returned.
    */
    i32Status = CsDo(hSystem, ACTION_COMMIT);
    //printf(_T("\n\ti32Status(CsDo) : %d\n"),i32Status); 

    if (CS_FAILED(i32Status))
    {
    DisplayErrorString(i32Status);
    CsFreeSystem(hSystem);
    VirtualFree (pArrayBoardInfo, 0, MEM_RELEASE);
    return (-1);
    }
    /*
    Get the current sample size, resolution and offset parameters from the driver
    by calling CsGet for the ACQUISTIONCONFIG structure. These values are used
    when saving the file.
    */
    CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
    i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);
    printf(_T("\n\ti32Status(CsGet) : %d\n"),i32Status); 
    if (CS_FAILED(i32Status))
    {
    DisplayErrorString(i32Status);
    CsFreeSystem(hSystem);
    VirtualFree (pArrayBoardInfo, 0, MEM_RELEASE);
    return (-1);
    }

    /*
    We need to allocate a buffer
    for transferring the data
    */
    pBuffer = VirtualAlloc(NULL, (size_t)((CsAppData.i64TransferLength + i64Padding) * CsAcqCfg.u32SampleSize), MEM_COMMIT, PAGE_READWRITE);
    //printf(_T("\n\tCsAppData.i64TransferLength : %ld"),CsAppData.i64TransferLength); 
    //printf(_T("\n\ti64Padding : %ld"),i64Padding); 
    //printf(_T("\n\tCsAcqCfg.u32SampleSize : %u"),CsAcqCfg.u32SampleSize); 
    //printf(_T("\n\tThe size of the allocated buffer : %lu\n"), (size_t)((CsAppData.i64TransferLength + i64Padding) * CsAcqCfg.u32SampleSize));
    //printf("*****************************************************\n");

    if (NULL == pBuffer)
    {
    printf (_T("\nUnable to allocate memory\n"));
    CsFreeSystem(hSystem);
    VirtualFree (pArrayBoardInfo, 0, MEM_RELEASE);
    return (-1);
    }

    if (TYPE_FLOAT == CsAppData.i32SaveFormat)
    {
    /*
    Allocate another buffer to pass the data that is going to be converted
    into voltages
    */
    pVBuffer = (float *)VirtualAlloc(NULL, (size_t)(CsAppData.i64TransferLength * sizeof(float)), MEM_COMMIT, PAGE_READWRITE);
    if (NULL == pVBuffer)
    {
    printf (_T("\nUnable to allocate memory\n"));
    CsFreeSystem(hSystem);
    VirtualFree(pBuffer, 0, MEM_RELEASE);
    VirtualFree (pArrayBoardInfo, 0, MEM_RELEASE);
    return (-1);
    }
    }
    printf("Gage card setting succeeded\n");
    return 0;
}