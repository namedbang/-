/**
  *****************************************************************************
  * Copyright (c) 2023,成都工业学院电子协会
  * All rights reserved.
  * 文件名称：PID.c
  * 摘    要：
  *           参考：https://blog.csdn.net/okgwf/article/details/120463142?spm=1001.2014.3001.5501
  *           特此鸣谢
  * 当前版本：V1.0
  * 作    者：成都工业学院电子协会 22级 谢邦琦
  * 完成日期：    
  * 修改说明：
  * 
  *
  * 历史版本：
  *
  *
  *****************************************************************************
**/	

#include "PID.h"

PID_t PID;

/*将角度转化为arr值*/
void PID_CCD_AngleTransF()
{
   float temp = 0;
   temp = PID.PID_Output*1.11f;
   PID.PID_OutputAngle=165+temp;
}
/*PID参数初始化*/
void PID_Init(void)
{
    PID.CCD_PID.P = -1.5;//1.36;
    PID.CCD_PID.I = -0.0001;//-0.006;
    PID.CCD_PID.D = -0.1;//-1.62;
}
/*位置式PID*/
float PID_Position(float Current_Value,float Target_Value)
{
    static float D_value_current,D_value_last,integral,output;
    
    D_value_current = Target_Value - Current_Value;
    integral+=D_value_current;
    
    output = PID.CCD_PID.P*D_value_current + PID.CCD_PID.I*integral + (D_value_current-D_value_last)*PID.CCD_PID.D;
    
    D_value_last = D_value_current;
    return output;
}
/*带输出端的反馈*/
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



