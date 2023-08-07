/**
  ******************************************************************************
  * Copyright (c) 2023,成都工业学院电子协会
  * All rights reserved.
  * 文件名称：CCD.c
  * 摘    要：
  *
  * 当前版本：V1.0
  * 作    者：成都工业学院电子协会 22级 谢邦琦
  * 完成日期：    
  * 修改说明：
  * 
  *
  * 历史版本：
  *
  *
  *******************************************************************************/
  
#include "CCD.h"

unsigned char CCD_Threshold;                 //线性CCD相关

unsigned int Get_Adc(void);
unsigned int myabs(int Input);

CCDT_t CCD;

/*计算中线偏差*/
void  Find_CCD_Median(void)
{ 
	static unsigned char i,j,Left,Right,Last_CCD_Median;
	static unsigned int value1_max,value1_min;

	value1_max=CCD.CCD_ADV[0];  //动态阈值算法，读取最大和最小值
	for(i=15;i<123;i++)   //两边各去掉15个点
	{
		if(value1_max<=CCD.CCD_ADV[i])
		value1_max=CCD.CCD_ADV[i];
	}
	value1_min=CCD.CCD_ADV[0];  //最小值
	for(i=15;i<123;i++) 
	{
		if(value1_min>=CCD.CCD_ADV[i])
		value1_min=CCD.CCD_ADV[i];
	}
	CCD_Threshold=(value1_max+value1_min)/2;	  //计算出本次中线提取的阈值
	for(i = 15;i<118; i++)   //寻找左边跳变沿
	{
		if(CCD.CCD_ADV[i]>CCD_Threshold&&CCD.CCD_ADV[i+1]>CCD_Threshold&&CCD.CCD_ADV[i+2]>CCD_Threshold&&CCD.CCD_ADV[i+3]<CCD_Threshold&&CCD.CCD_ADV[i+4]<CCD_Threshold&&CCD.CCD_ADV[i+5]<CCD_Threshold)
		{	
			Left=i;
			break;	
		}
	}
	for(j = 118;j>15; j--)//寻找右边跳变沿
	{
		if(CCD.CCD_ADV[j]<CCD_Threshold&&CCD.CCD_ADV[j+1]<CCD_Threshold&&CCD.CCD_ADV[j+2]<CCD_Threshold&&CCD.CCD_ADV[j+3]>CCD_Threshold&&CCD.CCD_ADV[j+4]>CCD_Threshold&&CCD.CCD_ADV[j+5]>CCD_Threshold)
		{	
			Right=j;
			break;	
		}
	}
	CCD.CCD_Median=(Right+Left)/2;//计算中线位置
	if(myabs(CCD.CCD_Median-Last_CCD_Median)>90)   //计算中线的偏差，如果太大
	    CCD.CCD_Median=Last_CCD_Median;    //则取上一次的值
	Last_CCD_Median=CCD.CCD_Median;  //保存上一次的偏差
}

void CCD_read(void)
{
    unsigned char i=0,tslp=0;
	
    CCD.CCD_state = 1;
    
	TSL_CLK_HIGH;
	TSL_SI_LOW;
	Dly_us();
	Dly_us();

	TSL_CLK_LOW;
	TSL_SI_LOW;
	Dly_us();
	Dly_us();

	TSL_CLK_LOW;
	TSL_SI_HIGH;
	Dly_us();
	Dly_us();

	TSL_CLK_HIGH;
	TSL_SI_HIGH;
	Dly_us();
	Dly_us();

	TSL_CLK_HIGH;
	TSL_SI_LOW;
	Dly_us();
	Dly_us();
	
	for(i=0;i<128;i++)
	{ 
		TSL_CLK_LOW; 
		Dly_us();  
		Dly_us();
		CCD.CCD_ADV[tslp]=(Get_Adc())>>4;		
		++tslp;
		TSL_CLK_HIGH;
		Dly_us();  
	}
    
    CCD.CCD_state = 0;
    
}
/*进行一次ADC采样*/
unsigned int Get_Adc(void)
{
//    HAL_ADC_Start(&hadc1);//开启ADC
//    HAL_ADC_PollForConversion(&hadc1,100);//等待ADC转换完成，超时为100ms
//    if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC)){
//         //读取值
//       return HAL_ADC_GetValue(&hadc1);
//    }
//    return 0;
    uint16_t temp = 0;
    ADC_convert(adc,&temp);
    return temp;
}
/*绝对值函数*/
unsigned int myabs(int Input)
{
	int Output;
	if(Input > 0)
		Output = Input;
	else
		Output = -Input;
	return Output;
}
/*延时函数*/
void Dly_us(void)
{
   int ii;    
   for(ii=0;ii<18;ii++);
}
