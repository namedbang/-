/**
  *****************************************************************************
  * Copyright (c) 2023,成都工业学院电子协会
  * All rights reserved.
  * 文件名称：communication.c
  * 摘    要：
  *           参考：https://blog.csdn.net/okgwf/article/details/120463142?spm=1001.2014.3001.5501
  *           特此鸣谢
  * 当前版本：V1.0
  * 作    者：成都工业学院电子协会 22级 谢邦琦 20届 向振权
  * 完成日期：
  * 修改说明：2032.8.1 谢邦琦修改向振权的数据长度
  *
  *
  * 历史版本：
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
        xSemaphoreTake(xSemaphore1,portMAX_DELAY);//释放二值信号量
        /*接收数据处理begin*/

        /*接收数据处理end*/
    }
}

int Temp = 0;
int size  = 0;
char single = 0;
unsigned char buff_er[20];

void UART_RxCpltCallback(UART_Handle handle, void *buf, size_t count)
{
    /**************20届 谢邦琦 的数据接收***************/
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
//    UART_read(uart, BuffFIFO, 16);//开启数据接收中断

/*****************20届 向振权 的数据接收*********************/
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
     UART_read(uart, BuffFIFO, 1);//开启数据接收中断
}
