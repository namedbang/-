/**
  ******************************************************************************
  * Copyright (c) 2023,�ɶ���ҵѧԺ����Э��
  * All rights reserved.
  * �ļ����ƣ�CCD.c
  * ժ    Ҫ��
  *
  * ��ǰ�汾��V1.0
  * ��    �ߣ��ɶ���ҵѧԺ����Э�� 22�� л����
  * ������ڣ�    
  * �޸�˵����
  * 
  *
  * ��ʷ�汾��
  *
  *
  *******************************************************************************/
  
#include "CCD.h"

unsigned char CCD_Threshold;                 //����CCD���

unsigned int Get_Adc(void);
unsigned int myabs(int Input);

CCDT_t CCD;

/*��������ƫ��*/
void  Find_CCD_Median(void)
{ 
	static unsigned char i,j,Left,Right,Last_CCD_Median;
	static unsigned int value1_max,value1_min;

	value1_max=CCD.CCD_ADV[0];  //��̬��ֵ�㷨����ȡ������Сֵ
	for(i=15;i<123;i++)   //���߸�ȥ��15����
	{
		if(value1_max<=CCD.CCD_ADV[i])
		value1_max=CCD.CCD_ADV[i];
	}
	value1_min=CCD.CCD_ADV[0];  //��Сֵ
	for(i=15;i<123;i++) 
	{
		if(value1_min>=CCD.CCD_ADV[i])
		value1_min=CCD.CCD_ADV[i];
	}
	CCD_Threshold=(value1_max+value1_min)/2;	  //���������������ȡ����ֵ
	for(i = 15;i<118; i++)   //Ѱ�����������
	{
		if(CCD.CCD_ADV[i]>CCD_Threshold&&CCD.CCD_ADV[i+1]>CCD_Threshold&&CCD.CCD_ADV[i+2]>CCD_Threshold&&CCD.CCD_ADV[i+3]<CCD_Threshold&&CCD.CCD_ADV[i+4]<CCD_Threshold&&CCD.CCD_ADV[i+5]<CCD_Threshold)
		{	
			Left=i;
			break;	
		}
	}
	for(j = 118;j>15; j--)//Ѱ���ұ�������
	{
		if(CCD.CCD_ADV[j]<CCD_Threshold&&CCD.CCD_ADV[j+1]<CCD_Threshold&&CCD.CCD_ADV[j+2]<CCD_Threshold&&CCD.CCD_ADV[j+3]>CCD_Threshold&&CCD.CCD_ADV[j+4]>CCD_Threshold&&CCD.CCD_ADV[j+5]>CCD_Threshold)
		{	
			Right=j;
			break;	
		}
	}
	CCD.CCD_Median=(Right+Left)/2;//��������λ��
	if(myabs(CCD.CCD_Median-Last_CCD_Median)>90)   //�������ߵ�ƫ����̫��
	    CCD.CCD_Median=Last_CCD_Median;    //��ȡ��һ�ε�ֵ
	Last_CCD_Median=CCD.CCD_Median;  //������һ�ε�ƫ��
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
/*����һ��ADC����*/
unsigned int Get_Adc(void)
{
//    HAL_ADC_Start(&hadc1);//����ADC
//    HAL_ADC_PollForConversion(&hadc1,100);//�ȴ�ADCת����ɣ���ʱΪ100ms
//    if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC)){
//         //��ȡֵ
//       return HAL_ADC_GetValue(&hadc1);
//    }
//    return 0;
    uint16_t temp = 0;
    ADC_convert(adc,&temp);
    return temp;
}
/*����ֵ����*/
unsigned int myabs(int Input)
{
	int Output;
	if(Input > 0)
		Output = Input;
	else
		Output = -Input;
	return Output;
}
/*��ʱ����*/
void Dly_us(void)
{
   int ii;    
   for(ii=0;ii<18;ii++);
}
