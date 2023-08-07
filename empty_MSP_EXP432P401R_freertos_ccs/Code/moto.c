/*
 * moto.c
 *
 *  Created on: 2023��7��31��
 *      Author: л����
 */

#include "moto.h"

Moto_t Moto;

void *Control_Task(void *arg0)
{
    while(1){
        /*�������begin*/
        CCD_read();
        Find_CCD_Median();
        GPIO_write(AIN1, 1);//ʹ��
        GPIO_write(AIN2, 0);//ʹ��
        GPIO_write(BIN1, 1);//ʹ��
        GPIO_write(BIN2, 0);//ʹ��
        PWM_setDuty(pwmA,500);
        PWM_setDuty(pwmB,500);
        /*�������end*/
        GPIO_toggle(CONFIG_GPIO_7);
        usleep(1);
    }
}

void CaptureCallbackFunctionL(Capture_Handle handle, uint32_t interval)
{
    GPIO_toggle(CONFIG_GPIO_8);
    Moto.EncoderVaule_l++;
}

void CaptureCallbackFunctionR(Capture_Handle handle, uint32_t interval)
{
    GPIO_toggle(CONFIG_GPIO_8);
    Moto.EncoderVaule_r++;
}
