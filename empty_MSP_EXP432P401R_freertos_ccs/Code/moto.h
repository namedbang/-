#ifndef moto_H_
#define moto_H_

#include "public.h"

void *Control_Task(void *arg0);
void CaptureCallbackFunctionL(Capture_Handle handle, uint32_t interval);
void CaptureCallbackFunctionR(Capture_Handle handle, uint32_t interval);

typedef struct{
    float V_r;
    float V_l;
    int   PWM_r;
    int   PWM_l;
    int   EncoderVaule_r;
    int   EncoderVaule_l;
}Moto_t;
extern Moto_t Moto;

extern PWM_Handle pwmA;
extern PWM_Handle pwmB;

#endif
