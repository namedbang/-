/*
 * communication.h
 *
 *  Created on: 2023��7��30��
 *      Author: л����
 */

#ifndef CODE_COMMUNICATION_H_
#define CODE_COMMUNICATION_H_

#include "stdbool.h"
#include "public.h"

#define data_size  15

#pragma pack (1)
typedef struct
{
    char hand;
    char xnms;
    int V_car;
    float CarX;
    float CarY;
    char chank;
    char End;
}Link_Head_t;
#pragma pack ()
extern Link_Head_t Link_Head;

#pragma pack (1)
typedef struct
{
    char xnms;
    int V_car;
    float CarX;
    float CarY;
    double Angle;
}RemoteControl_t;
#pragma pack ()
extern RemoteControl_t RemoteControl;

extern unsigned char BuffFIFO[30];
extern UART_Handle uart;
extern QueueHandle_t xSemaphore1;//������ֵ�ź������

void *Communication_Task(void *arg0);
void UART_RxCpltCallback(UART_Handle handle, void *buf, size_t count);

#endif /* CODE_COMMUNICATION_H_ */
