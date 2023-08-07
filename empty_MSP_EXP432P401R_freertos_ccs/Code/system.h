#ifndef system_H_
#define system_H_

#include "moto.h"
#include "MPU6050.H"
#include "communication.h"
#include "PID.h"
#include "CCD.h"

typedef struct{
    Moto_t *MotoPr;
    RemoteControl_t *RcPr;
    PID_t *PidVaule;
    CCDT_t *CCD_Pr;
}systemInfo_t;
extern systemInfo_t systemInfo;

#endif
