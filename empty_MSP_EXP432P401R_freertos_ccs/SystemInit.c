/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
/*
 *  ======== SystemInit.c ========
 */
#include "system.h"
#include "public.h"
#include "communication.h"

systemInfo_t systemInfo;
UART_Params param;
UART_Handle uart;
SemaphoreHandle_t xSemaphore1 = NULL;//创建二值信号量句柄
Display_Handle    handleD;
Display_Params    paramsD;
Timer_Handle    handleT;
Timer_Params    paramsT;
Capture_Handle    handleC_l;
Capture_Handle    handleC_r;
Capture_Params    paramsC;
PWM_Handle pwmA;
PWM_Handle pwmB;
PWM_Params pwmParams;
ADC_Handle adc;
ADC_Params paramsADC;

void timerCallback(Timer_Handle myHandle);
/*
 *  ======== mainThread ========
 */
void *SystemInit_Task(void *arg0)
{
    /*************GPIO模块*******************/
    GPIO_init();
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
    /*************Display模块****************/
    Display_Params_init(&paramsD);
    handleD = Display_open(Display_Type_UART, &paramsD);
    /****************UART模块****************/
    UART_init();
    UART_Params_init(&param);
    param.baudRate = 9600;
    param.readMode = UART_MODE_CALLBACK;
    param.writeMode = UART_MODE_BLOCKING;
    param.readCallback = UART_RxCpltCallback;
    param.readTimeout = UART_WAIT_FOREVER;
    param.writeTimeout = UART_WAIT_FOREVER;
    param.readEcho = UART_ECHO_OFF;
    uart = UART_open(CONFIG_UART_0, &param);
    UART_read(uart, BuffFIFO, 1);
    GPIO_toggle(CONFIG_GPIO_0);
    /****************定时器模块（1ms）****************/
    Timer_init();
    Timer_Params_init(&paramsT);
    paramsT.periodUnits = Timer_PERIOD_US;
    paramsT.period = 1000;
    paramsT.timerMode  = Timer_CONTINUOUS_CALLBACK;
    paramsT.timerCallback = timerCallback;
    handleT = Timer_open(CONFIG_TIMER_1, &paramsT);
    Timer_start(handleT);
    /******************编码器模块（输入捕获）*************/
    Capture_init();
    Capture_Params_init(&paramsC);
    paramsC.mode  = Capture_ANY_EDGE;
    paramsC.callbackFxn = CaptureCallbackFunctionL;
    paramsC.periodUnit = Capture_PERIOD_COUNTS;
    handleC_l = Capture_open(CONFIG_CAPTURE_1, &paramsC);
    Capture_start(handleC_l);
    paramsC.callbackFxn = CaptureCallbackFunctionR;
    handleC_r = Capture_open(CONFIG_CAPTURE_2, &paramsC);
    Capture_start(handleC_r);
    /******************电机初始化（PWM）*************/
    PWM_init();
    PWM_Params_init(&pwmParams);
    pwmParams.idleLevel = PWM_IDLE_LOW;
    pwmParams.periodUnits = PWM_PERIOD_COUNTS;
    pwmParams.periodValue = 1000;
    pwmParams.dutyUnits = PWM_DUTY_COUNTS;
    pwmParams.dutyValue = 500;
    pwmA = PWM_open(CONFIG_PWM_A, &pwmParams);
    pwmB = PWM_open(CONFIG_PWM_B, &pwmParams);
    PWM_start(pwmA);
    PWM_start(pwmB);
    GPIO_write(STBY, 0);//使能
    /******************ADC初始化（CCD）*************/
    ADC_init();
    ADC_Params_init(&paramsADC);
    paramsADC.isProtected = true;
    adc = ADC_open(0, &paramsADC);
    /********系统文件配置（写入systemInfo结构体）*********/
    systemInfo.MotoPr = &Moto;
    systemInfo.RcPr = &RemoteControl;
    systemInfo.PidVaule = &PID;
    systemInfo.CCD_Pr = &CCD;
    /**************FreeRTOS相关********************/
    xSemaphore1 = xSemaphoreCreateBinary();//创建二值信号量
    /**************陀螺仪相关***********************/
    MPU_Init();
    while (1) {
        mpu_update();
        Display_print3(handleD, 0, 0, "%f %f %f",angleX,angleY,angleZ);
    }
}

int time1 = 0;
int time2 = 0;
void timerCallback(Timer_Handle myHandle)
{
    timer++;
    time1++;//运行标志
    time2++;
    if(time1%1000 == 0){
        time1 = 0;
        GPIO_toggle(CONFIG_GPIO_LED_0);
    }
    if(time2%10 == 0){//10ms编码器计算速度
        time2 = 0;
        Moto.V_l = Moto.EncoderVaule_l*100.0f/30.f/13.0f/(67.0f*3.14)/2;
        Moto.V_r = Moto.EncoderVaule_r*100.0f/30.f/13.0f/(67.0f*3.14)/2;
        Moto.EncoderVaule_l = 0;
        Moto.EncoderVaule_r = 0;
    }
    Timer_start(handleT);
}
