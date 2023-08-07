/*
 * iic.c
 *
 *  Created on: 2023��6��15��
 *      Author: bang
 */
#include "iic.h"

#define NULL 0

I2C_Handle hi2c1;

// ������ʱ����������Ϊ��ʱ��΢����
void delay_us(uint32_t microseconds) {
    // ����ϵͳʱ��Ƶ��Ϊ3 MHz
    uint32_t cycles = microseconds * 3;

    // ִ����ʱѭ��
    while (cycles > 0) {
//        __delay_cycles(1);
        cycles--;
    }
}

void My_I2C_Init(I2C_Handle *hi2cHandle, uint_least8_t index)
{
    // One-time init of I2C driver
    I2C_init();
    // initialize optional I2C bus parameters
    I2C_Params params;
    I2C_Params_init(&params);
    params.bitRate = I2C_400kHz;
    // Open I2C bus for usage
    *hi2cHandle = I2C_open(index, &params);
}

bool My_I2C_Read(I2C_Handle *hi2cHandle, uint_least8_t slaveAddress, uint8_t *readBuf, size_t readCount)
{
    I2C_Transaction transaction = {0};
    transaction.slaveAddress = slaveAddress;
    transaction.writeBuf = NULL;
    transaction.writeCount = 0;
    // Read from I2C slave device
    transaction.readBuf = readBuf;
    transaction.readCount = readCount;
    return I2C_transfer(*hi2cHandle, &transaction);
}

bool My_I2C_Write(I2C_Handle *hi2cHandle, uint_least8_t slaveAddress, uint8_t *writeBuf, size_t writeCount)
{
    I2C_Transaction transaction = {0};
    transaction.slaveAddress = slaveAddress;
    transaction.readBuf = NULL;
    transaction.readCount = 0;
    // Write to I2C slave device
    transaction.writeBuf = writeBuf;
    transaction.writeCount = writeCount;
    return I2C_transfer(*hi2cHandle, &transaction);
}
/*
 * my_i2c.c
 *
 *  Created on: 2021��7��29��
 *      Author: Administrator
 */
void IIC_Init (void){
    IIC_SCL_High();
    IIC_SDA_High();
}

void IIC_Start(void)//SDA 10 SCL 010
{
    SDA_OUT();     //sda�����
    IIC_SCL_High();
    IIC_SDA_High();
    delay_us(4);
    IIC_SDA_Low();//START:when CLK is high,DATA change form high to low
    delay_us(4);
    IIC_SCL_Low();//ǯסI2C���ߣ�׼�����ͻ��������
}

void IIC_Stop(void)//SDA 01 SCL 01
{
    SDA_OUT();//sda�����
    IIC_SCL_Low();//STOP:when CLK is high DATA change form low to high
    IIC_SDA_Low();
    delay_us(4);
    IIC_SCL_High();
    IIC_SDA_High();//����I2C���߽����ź�
    delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(void)//
{
    uint8_t cy;
    SDA_IN();      //SDA����Ϊ����
    IIC_SCL_High();delay_us(10);
    IIC_SDA_High();delay_us(10);
    if(READ_SDA)
    {
        cy=1;
        IIC_SCL_Low();
        return cy;
    }
    else
    {
        cy=0;
    }
    IIC_SCL_Low();//ʱ�����0
    return cy;
}
//����ACKӦ��
void IIC_Ack(void)
{
    IIC_SCL_Low();
    SDA_OUT();
    IIC_SDA_Low();
    delay_us(2);
    IIC_SCL_High();
    delay_us(2);
    IIC_SCL_Low();
}
//������ACKӦ��
void IIC_NAck(void)
{
    IIC_SCL_Low();
    SDA_OUT();
    IIC_SDA_High();
    delay_us(2);
    IIC_SCL_High();
    delay_us(2);
    IIC_SCL_Low();
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL_Low();//����ʱ�ӿ�ʼ���ݴ���
    delay_us(2);
    for(t=0;t<8;t++)
    {
        if(txd&0x80)
        {
            IIC_SDA_High();delay_us(2);
        }
        else
        {
            IIC_SDA_Low();delay_us(2);
        }
        txd<<=1;
        IIC_SCL_High();
        delay_us(4);
        IIC_SCL_Low();
        delay_us(2);
    }
        delay_us(2);

}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
        IIC_SCL_Low();
        delay_us(2);
        IIC_SCL_High();
        receive<<=1;
        if(READ_SDA)
            receive++;
        delay_us(2);
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;

}





