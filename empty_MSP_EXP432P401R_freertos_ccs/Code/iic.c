/*
 * iic.c
 *
 *  Created on: 2023年6月15日
 *      Author: bang
 */
#include "iic.h"

#define NULL 0

I2C_Handle hi2c1;

// 定义延时函数，参数为延时的微秒数
void delay_us(uint32_t microseconds) {
    // 假设系统时钟频率为3 MHz
    uint32_t cycles = microseconds * 3;

    // 执行延时循环
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
 *  Created on: 2021年7月29日
 *      Author: Administrator
 */
void IIC_Init (void){
    IIC_SCL_High();
    IIC_SDA_High();
}

void IIC_Start(void)//SDA 10 SCL 010
{
    SDA_OUT();     //sda线输出
    IIC_SCL_High();
    IIC_SDA_High();
    delay_us(4);
    IIC_SDA_Low();//START:when CLK is high,DATA change form high to low
    delay_us(4);
    IIC_SCL_Low();//钳住I2C总线，准备发送或接收数据
}

void IIC_Stop(void)//SDA 01 SCL 01
{
    SDA_OUT();//sda线输出
    IIC_SCL_Low();//STOP:when CLK is high DATA change form low to high
    IIC_SDA_Low();
    delay_us(4);
    IIC_SCL_High();
    IIC_SDA_High();//发送I2C总线结束信号
    delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)//
{
    uint8_t cy;
    SDA_IN();      //SDA设置为输入
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
    IIC_SCL_Low();//时钟输出0
    return cy;
}
//产生ACK应答
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
//不产生ACK应答
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL_Low();//拉低时钟开始数据传输
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
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;

}





