/**
  *****************************************************************************
  * Copyright (c) 2023,�ɶ���ҵѧԺ����Э��
  * All rights reserved.
  * �ļ����ƣ�PID.c
  * ժ    Ҫ��
  *           �ο���https://blog.csdn.net/okgwf/article/details/120463142?spm=1001.2014.3001.5501
  *           �ش���л
  * ��ǰ�汾��V1.0
  * ��    �ߣ��ɶ���ҵѧԺ����Э�� 22�� л����
  * ������ڣ�    
  * �޸�˵����
  * 
  *
  * ��ʷ�汾��
  *
  *
  *****************************************************************************
**/	

#include "PID.h"

PID_t PID;

/*���Ƕ�ת��Ϊarrֵ*/
void PID_CCD_AngleTransF()
{
   float temp = 0;
   temp = PID.PID_Output*1.11f;
   PID.PID_OutputAngle=165+temp;
}
/*PID������ʼ��*/
void PID_Init(void)
{
    PID.CCD_PID.P = -1.5;//1.36;
    PID.CCD_PID.I = -0.0001;//-0.006;
    PID.CCD_PID.D = -0.1;//-1.62;
}
/*λ��ʽPID*/
float PID_Position(float Current_Value,float Target_Value)
{
    static float D_value_current,D_value_last,integral,output;
    
    D_value_current = Target_Value - Current_Value;
    integral+=D_value_current;
    
    output = PID.CCD_PID.P*D_value_current + PID.CCD_PID.I*integral + (D_value_current-D_value_last)*PID.CCD_PID.D;
    
    D_value_last = D_value_current;
    return output;
}
/*������˵ķ���*/
float PID_PositionOutputFeedback(float Current_Value,float Target_Value,float Control_Value)
{
    static float D_value_current,D_value_last,integral,output,NowValue; 
    
    NowValue = Control_Value+Current_Value;
    D_value_current = Target_Value - NowValue;
    integral+=D_value_current;
    
    output = PID.CCD_PID.P*D_value_current + PID.CCD_PID.I*integral + (D_value_current-D_value_last)*PID.CCD_PID.D;
    
    D_value_last = D_value_current;
    return output;
}



