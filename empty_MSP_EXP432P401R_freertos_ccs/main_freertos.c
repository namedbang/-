/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
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

/*
 *  ======== main_freertos.c ========
 */
#include <stdint.h>

#ifdef __ICCARM__
#include <DLib_Threads.h>
#endif

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

/* Driver configuration */
#include <ti/drivers/Board.h>
#include "moto.h"
#include "system.h"

extern void *SystemInit_Task(void *arg0);
extern void *Control_Task(void *arg0);
extern void *Communication_Task(void *arg0);

/* Stack size in bytes */
#define THREADSTACKSIZE   1024

/*
 *  ======== main ========
 */
int main(void)
{
    pthread_t           thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;

    pthread_t           thread1;
    pthread_attr_t      attrs1;
    struct sched_param  priParam1;
    int                 retc1;

    pthread_t           thread2;
    pthread_attr_t      attrs2;
    struct sched_param  priParam2;
    int                 retc2;

#ifdef __ICCARM__
    __iar_Initlocks();
#endif

    Board_init();
/**************************************************************/
    pthread_attr_init(&attrs);
    priParam.sched_priority = 1;
    retc = pthread_attr_setschedparam(&attrs, &priParam);
    retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        while (1) {}
    }

    retc = pthread_create(&thread, &attrs, SystemInit_Task, NULL);
    if (retc != 0) {
        while (1) {}
    }
/*************************************************************/
    pthread_attr_init(&attrs1);
    priParam1.sched_priority = 1;
    retc1 = pthread_attr_setschedparam(&attrs1, &priParam1);
    retc1 |= pthread_attr_setdetachstate(&attrs1, PTHREAD_CREATE_DETACHED);
    retc1 |= pthread_attr_setstacksize(&attrs1, THREADSTACKSIZE);
    if (retc1 != 0) {
        while (1) {}
    }

    retc1 = pthread_create(&thread1, &attrs1, Control_Task, NULL);
    if (retc1 != 0) {
        while (1) {}
    }
/*************************************************************/
    pthread_attr_init(&attrs2);
    priParam2.sched_priority = 1;
    retc2 = pthread_attr_setschedparam(&attrs2, &priParam2);
    retc2 |= pthread_attr_setdetachstate(&attrs2, PTHREAD_CREATE_DETACHED);
    retc2 |= pthread_attr_setstacksize(&attrs2, THREADSTACKSIZE);
    if (retc2 != 0) {
        while (1) {}
    }

    retc2 = pthread_create(&thread2, &attrs2, Communication_Task, NULL);
    if (retc2 != 0) {
        while (1) {}
    }
//*************************************************************/
    vTaskStartScheduler();
    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
