#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <pthread.h>

#include <cstdlib>
#include <iostream>

#include "printf.h"

#define QUEUE_DATA_TYPE uint8_t

/*
struct 结构体的大小采用对其的方式 
*/

typedef struct
{
    QUEUE_DATA_TYPE *Out; /* 指向数据输出位置         */
    QUEUE_DATA_TYPE *In;  /* 指向数据输入位置         */
    QUEUE_DATA_TYPE *End; /* 指向Buf的结束位置        */
    uint64_t NData;       /* 队列中数据个数           */
    uint64_t MaxData;     /* 队列中允许存储的数据个数 */

    uint8_t (*ReadEmpty)(); /* 读空处理函数             */
    uint8_t (*WriteFull)(); /* 写满处理函数             */
    QUEUE_DATA_TYPE Buf[1]; /* 存储数据的空间           */
} DataQueue;

uint8_t QueueCreate(void *Buf,
                    uint64_t SizeOfBuf,
                    uint8_t (*ReadEmpty)(),
                    uint8_t (*WriteFull)())
{
    // printf("%s %d\n",__func__,__LINE__);
    DataQueue *Queue;
    if (Buf != NULL && SizeOfBuf >= (sizeof(DataQueue)))
    {
        // printf("%ld \n",aa);
        uint64_t aa = (uint64_t)(((DataQueue *)0)->Buf);
        Queue->MaxData = (SizeOfBuf - (uint64_t)(((DataQueue *)0)->Buf)) /
                         sizeof(QUEUE_DATA_TYPE);
        // printf("%s %d\n", __func__, __LINE__);
        Queue->End = Queue->Buf + Queue->MaxData;
        Queue->Out = Queue->Buf;
        Queue->In = Queue->Buf;
        Queue->NData = 0;
        Queue->ReadEmpty = ReadEmpty;
        Queue->WriteFull = WriteFull;
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t UpRecQueue_Gprs[1000000];
uint8_t USART3RecQueue_At[1000000];

#define UP_COMMU_DEV_ARRAY 8 //指明上面上行通讯设备的数量。

//上行通信设备ID ，这些常量的值直接作为全局数组的下标使用，因此不能随便修改
#define UP_COMMU_DEV_ZIGBEE 0
#define UP_COMMU_DEV_485 1
#define UP_COMMU_DEV_232 2
#define UP_COMMU_DEV_GPRS 3
#define UP_COMMU_DEV_AT 4
#define UP_COMMU_DEV_ATIPD 5
#define DOWN_COMMU_DEV_485 6
#define DOWN_COMMU_DEV_MBUS 7

uint8_t *pQueues[UP_COMMU_DEV_ARRAY];

uint8_t QueuesInit(void)
{
    if (QueueCreate((void *)UpRecQueue_Gprs, sizeof(UpRecQueue_Gprs), NULL, NULL) == 1)
    {
        return 1;
    }

    if (QueueCreate((void *)USART3RecQueue_At, sizeof(USART3RecQueue_At), NULL, NULL) == 1)
    {
        return 1;
    }
    return 0;
}

uint8_t UpcommapInit(void)
{
    pQueues[UP_COMMU_DEV_GPRS] = UpRecQueue_Gprs;
    pQueues[UP_COMMU_DEV_AT] = USART3RecQueue_At;

    return 0;
}

// struct node
// {
// 	// uint8_t *a;
// 	// uint8_t *b;
// 	// uint8_t *c;
//     uint32_t NData;       /* 队列中数据个数           */
//     uint32_t MaxData;     /* 队列中允许存储的数据个数 */
//     uint8_t a;
//     // uint8_t (*ReadEmpty)(); /* 读空处理函数             */
//     // uint8_t (*WriteFull)(); /* 写满处理函数             */
//     // uint8_t aa; /* 存储数据的空间           */
// };

// int main()
// {
// 	struct node QING;

// 	printf("%ld\n",sizeof(QING));

// 	return 0;
// }

int8_t pthread_GPRS_Mana()
{

    return 0;
}

// void create_pthread_GprsRelated(void)
// {
//     int32_t lReg = 0;
//     pthread_t GPRS_Mana_pthreadID;  //GPRS管理线程ID.
//     pthread_t GPRS_IPD_pthreadID;  //GPRS网络传输数据处理线程ID.
//     pthread_t GprsDataDeal_pthreadID;  //GPRS网络传输数据处理线程ID.

//     // lReg = pthread_create(&GPRS_Mana_pthreadID,NULL,(void *)pthread_GPRS_Mana,NULL);
//     if(0 != lReg){
//         	// printf ("Create pthread_GPRS_Mana error!\n");
//         	// exit (1);
//     }
//     else
//         printf ("Create pthread_GPRS_Mana OK!\n");

//     // lReg = pthread_create(&GPRS_IPD_pthreadID,NULL,(void *)pthread_GPRS_IPD,NULL);
//     if(0 != lReg){
//         	printf ("Create pthread_GPRS_IPD error!\n");
//         	exit (1);
//     }
//     else
//         printf ("Create pthread_GPRS_IPD OK!\n");

//     // lReg = pthread_create(&GprsDataDeal_pthreadID,NULL,(void *)pthread_GprsDataDeal,NULL);
//     if(0 != lReg){
//         printf ("Create pthread_GprsDataDeal error!\n");
//         exit (1);
//     }
//     else
//         printf ("Create pthread_GprsDataDeal OK!\n");
// }

int main()
{

    UpcommapInit();
    QueuesInit();

    DataQueue a;
    print();

    printf("%ld\n", sizeof(a));
    return 0;
}