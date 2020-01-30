#include "I2C.h"

void i2c_init(void)
{
	GPIO_InitTypeDef GPIO_InitStr;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能??
	
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStr.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStr.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE,&GPIO_InitStr);
	
	
}

void i2c_start(void)
{
	SDA_IO_OUT();
	SDA = 1;                    //拉高数据线
  SCL = 1;                    //拉高时钟线
  delay_us(5);
  SDA = 0;                    //产生下降沿
  delay_us(5);                 //延时
  SCL = 0;                    //拉低时钟线
}

void i2c_stop()
{
	SDA_IO_OUT();
	SDA = 0;                    //拉低数据线
	SCL = 1;                    //拉高时钟线
	delay_us(5);                 //延时
	SDA = 1;                    //产生上升沿
	delay_us(5);                 //延时
}

void i2c_sendack(unsigned char ack)
{
	SDA_IO_OUT();
	SDA = ack;                  //写应答信号
	SCL = 1;                    //拉高时钟线
	delay_us(5);                 //延时
	SCL = 0;                    //拉低时钟线
	delay_us(5);                 //延时
}

unsigned char i2c_recvack()
{
	unsigned char ack = 0;
	SDA_IO_IN();
	SCL = 1;                    //拉高时钟线
	delay_us(5);                 //延时
	if(READ_SDA)
		ack = 1;                   //读应答信号
	else 
		ack = 0;
	SCL = 0;                    //拉低时钟线
	delay_us(5);                 //延时

	return ack;
}

void i2c_sendbyte(unsigned char data)
{
	unsigned char i;
	
	SDA_IO_OUT();
	
	SDA = 0;
	for (i = 0; i < 8; i++)         //8位计数器
	{
		if(data & 0X80)
			SDA = 1;         //移出数据的最高位,送数据口
		else 
			SDA = 0;
			SCL = 1;                //拉高时钟线
			delay_us(5);            //延时
			SCL = 0;                //拉低时钟线
			delay_us(5);             //延时
			data <<= 1;
			delay_us(5);             //延时
	}
	i2c_recvack();
	
}

unsigned char i2c_recvbyte()
{
	unsigned char data;
	unsigned char i;
	SDA_IO_IN();

	for (i = 0; i < 8; i++)         //8位计数器
	{
			data <<= 1;
			SCL = 1;                //拉高时钟线
			delay_us(2);             //延时
			if(READ_SDA)
				data |= 1;             //读数据  
			else data |= 0;
			SCL = 0;                //拉低时钟线
			delay_us(2);             //延时
	}
	return data;
}
