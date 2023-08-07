/*
 * iic.h
 *
 *  Created on: 2023��6��15��
 *      Author: Administrator
 */

#ifndef iic_H
#define iic_H

// Import I2C Driver definitions
#include <ti/drivers/I2C.h>
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"
#include "unistd.h"

void My_I2C_Init(I2C_Handle *hi2cHandle, uint_least8_t index);
bool My_I2C_Write(I2C_Handle *hi2cHandle, uint_least8_t slaveAddress, uint8_t *writeBuf, size_t writeCount);
bool My_I2C_Read(I2C_Handle *hi2cHandle, uint_least8_t slaveAddress, uint8_t *readBuf, size_t   readCount);

extern I2C_Handle hi2c1;

#define SDA_IN()  GPIO_setConfig(mpu6050_sda, GPIO_CFG_INPUT)
#define SDA_OUT() GPIO_setConfig(mpu6050_sda, GPIO_CFG_OUT_STD)

#define IIC_SCL_High()  GPIO_write(mpu6050_scl,1) //SCL_High
#define IIC_SCL_Low()   GPIO_write(mpu6050_scl,0) //SCL_Low
#define IIC_SDA_High()  GPIO_write(mpu6050_sda,1)//SDA_High
#define IIC_SDA_Low()   GPIO_write(mpu6050_sda,0) //SDA_Low
#define READ_SDA        GPIO_read(mpu6050_sda)//����SDA

void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);               //����IIC��ʼ�ź�
void IIC_Stop(void);                //����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);         //IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void IIC_Ack(void);                 //IIC����ACK�ź�
void IIC_NAck(void);                //IIC������ACK�ź�

#endif /* CODE_IIC_LIB_IIC_H_ */
