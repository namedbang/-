#ifndef _CCD_H
#define _CCD_H

#include "public.h"

#define TSL_CLK_HIGH GPIO_write(CCD_clk,1)
#define TSL_CLK_LOW GPIO_write(CCD_clk,0)
#define TSL_SI_HIGH GPIO_write(CCD_SI,1)
#define TSL_SI_LOW GPIO_write(CCD_SI,0)
//#define CCD_Median CCD.CCD_median

void Dly_us(void);
void CCD_read(void);
void Find_CCD_Median(void);

extern ADC_Handle adc;

typedef struct{
  unsigned int CCD_ADV[128];
  char CCD_Median;
  char CCD_state;
}CCDT_t;
extern CCDT_t CCD;

#endif
