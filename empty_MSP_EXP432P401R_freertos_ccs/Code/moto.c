/*
 * moto.c
 *
 *  Created on: 2023年7月31日
 *      Author: 谢邦琦
 */

#include "moto.h"

Moto_t Moto;

void *Control_Task(void *arg0)
{
    while(1){
        /*电机控制begin*/
        CCD_read();
        Find_CCD_Median();
        GPIO_write(AIN1, 1);//使能
        GPIO_write(AIN2, 0);//使能
        GPIO_write(BIN1, 1);//使能
        GPIO_write(BIN2, 0);//使能
        PWM_setDuty(pwmA,500);
        PWM_setDuty(pwmB,500);
        /*电机控制end*/
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
