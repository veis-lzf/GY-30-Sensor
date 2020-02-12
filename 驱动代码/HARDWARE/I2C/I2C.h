#ifndef __I2C_H
#define __I2C_H

#include "sys.h"
#include "delay.h"

#define SDA_IO_IN()  {GPIOE->MODER&=~(3<<(2*2));GPIOE->MODER|=0<<2*2;}	//PE2输入模式
#define SDA_IO_OUT() {GPIOE->MODER&=~(3<<(2*2));GPIOE->MODER|=1<<2*2;} 	//PE2输出模式 

#define SCL PEout(3)
#define SDA PEout(2)
#define READ_SDA PEin(2)


void i2c_init(void);
void i2c_start(void);			
void i2c_stop(void);
void i2c_sendack(unsigned char ack);
unsigned char i2c_recvack(void);
void i2c_sendbyte(unsigned char data);
unsigned char i2c_recvbyte(void);

#endif


