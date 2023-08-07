#ifndef _PID_H
#define _PID_H

typedef struct {
    float P;
    float I;
    float D;
}CCD_PID_t;

typedef struct {
    CCD_PID_t CCD_PID;
    float PID_Output;
    float PID_OutputAngle;
}PID_t;
extern PID_t PID;

void PID_Init(void);
float PID_Position(float Current_Value,float Target_Value);
void PID_CCD_AngleTransF(void);
float PID_PositionOutputFeedback(float Current_Value,float Target_Value,float Control_Value);

#endif
