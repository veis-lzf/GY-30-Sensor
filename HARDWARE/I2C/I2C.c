#include "I2C.h"

void i2c_init(void)
{
	GPIO_InitTypeDef GPIO_InitStr;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��??
	
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
	SDA = 1;                    //����������
  SCL = 1;                    //����ʱ����
  delay_us(5);
  SDA = 0;                    //�����½���
  delay_us(5);                 //��ʱ
  SCL = 0;                    //����ʱ����
}

void i2c_stop()
{
	SDA_IO_OUT();
	SDA = 0;                    //����������
	SCL = 1;                    //����ʱ����
	delay_us(5);                 //��ʱ
	SDA = 1;                    //����������
	delay_us(5);                 //��ʱ
}

void i2c_sendack(unsigned char ack)
{
	SDA_IO_OUT();
	SDA = ack;                  //дӦ���ź�
	SCL = 1;                    //����ʱ����
	delay_us(5);                 //��ʱ
	SCL = 0;                    //����ʱ����
	delay_us(5);                 //��ʱ
}

unsigned char i2c_recvack()
{
	unsigned char ack = 0;
	SDA_IO_IN();
	SCL = 1;                    //����ʱ����
	delay_us(5);                 //��ʱ
	if(READ_SDA)
		ack = 1;                   //��Ӧ���ź�
	else 
		ack = 0;
	SCL = 0;                    //����ʱ����
	delay_us(5);                 //��ʱ

	return ack;
}

void i2c_sendbyte(unsigned char data)
{
	unsigned char i;
	
	SDA_IO_OUT();
	
	SDA = 0;
	for (i = 0; i < 8; i++)         //8λ������
	{
		if(data & 0X80)
			SDA = 1;         //�Ƴ����ݵ����λ,�����ݿ�
		else 
			SDA = 0;
			SCL = 1;                //����ʱ����
			delay_us(5);            //��ʱ
			SCL = 0;                //����ʱ����
			delay_us(5);             //��ʱ
			data <<= 1;
			delay_us(5);             //��ʱ
	}
	i2c_recvack();
	
}

unsigned char i2c_recvbyte()
{
	unsigned char data;
	unsigned char i;
	SDA_IO_IN();

	for (i = 0; i < 8; i++)         //8λ������
	{
			data <<= 1;
			SCL = 1;                //����ʱ����
			delay_us(2);             //��ʱ
			if(READ_SDA)
				data |= 1;             //������  
			else data |= 0;
			SCL = 0;                //����ʱ����
			delay_us(2);             //��ʱ
	}
	return data;
}
