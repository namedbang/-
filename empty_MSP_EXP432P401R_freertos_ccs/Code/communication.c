/**
  *****************************************************************************
  * Copyright (c) 2023,�ɶ���ҵѧԺ����Э��
  * All rights reserved.
  * �ļ����ƣ�communication.c
  * ժ    Ҫ��
  *           �ο���https://blog.csdn.net/okgwf/article/details/120463142?spm=1001.2014.3001.5501
  *           �ش���л
  * ��ǰ�汾��V1.0
  * ��    �ߣ��ɶ���ҵѧԺ����Э�� 22�� л���� 20�� ����Ȩ
  * ������ڣ�
  * �޸�˵����2032.8.1 л�����޸�����Ȩ�����ݳ���
  *
  *
  * ��ʷ�汾��
  *
  *
  *****************************************************************************
**/
#include "communication.h"

Link_Head_t Link_Head;
RemoteControl_t RemoteControl;

unsigned char BuffFIFO[30] = {0};

void *Communication_Task(void *arg0)
{
    while(1){
        xSemaphoreTake(xSemaphore1,portMAX_DELAY);//�ͷŶ�ֵ�ź���
        /*�������ݴ���begin*/

        /*�������ݴ���end*/
    }
}

int Temp = 0;
int size  = 0;
char single = 0;
unsigned char buff_er[20];

void UART_RxCpltCallback(UART_Handle handle, void *buf, size_t count)
{
    /**************20�� л���� �����ݽ���***************/
//    Temp = 0;
//    memcpy((unsigned char *)&Link_Head,BuffFIFO,16);
//    if(BuffFIFO[0] == 0xA5 && BuffFIFO[15] == 0x5A){
//        for(int i = 1;i<=13;i++){
//            Temp+=BuffFIFO[i];
//        }
//        Temp&=0xff;
//        if(Temp == BuffFIFO[14]){
//            memcpy((unsigned char *)&RemoteControl,BuffFIFO+1,13);
//        }
//        else{
//            GPIO_toggle(CONFIG_GPIO_0);
//        }
//    }else{
//        GPIO_toggle(CONFIG_GPIO_0);
//    }
//    //if(BuffFIFO[9] != 0xbf&&BuffFIFO[13] != 0xbf)
//    xSemaphoreGiveFromISR(xSemaphore1,NULL);
//    UART_read(uart, BuffFIFO, 16);//�������ݽ����ж�

/*****************20�� ����Ȩ �����ݽ���*********************/
    if(BuffFIFO[0]==0xA5&&single==0)
        single = 1;
    if(single==1)
    {
        buff_er[size] = BuffFIFO[0];
        size++;
        if(size==data_size+1)
        {
            size=0;
            single=0;
            memcpy((unsigned char *)&Link_Head,buff_er,data_size+1);
        }
    }
     UART_read(uart, BuffFIFO, 1);//�������ݽ����ж�
}
