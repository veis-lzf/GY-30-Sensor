#include "BH1750FVI.h"

void init_BH1750()
{
	i2c_init();
	single_write_BHB1750(0x01);  //POWER ON MODE
}

void single_write_BHB1750(unsigned char REG_Address)
{
	i2c_start();
	i2c_sendbyte(SlaveAddress + WRITE);
	i2c_sendbyte(REG_Address);
	i2c_stop();	
}
unsigned char single_read_BH1750(unsigned char REG_Address)
{
	unsigned char REG_data;
	i2c_start();                          //起始信号
	i2c_sendbyte(SlaveAddress + WRITE);           //发送设备地址+写信号
	i2c_sendbyte(REG_Address);                   //发送存储单元地址，从0开始	
	i2c_stop();
	
	delay_us(5);
	
	i2c_start();                          //起始信号
	i2c_sendbyte(SlaveAddress + READ);         //发送设备地址+读信号
	REG_data=i2c_recvbyte();              //读出寄存器数据
	i2c_sendack(0);   
	i2c_stop();                           //停止信号
	
	return REG_data; 
}
float multiple_read_BH1750()
{
  unsigned char i;
	float tmp;
	unsigned int dis_data = 0;
	
	i2c_start();
	i2c_sendbyte(SlaveAddress + READ);
	
	for(i = 0; i < 3; i++)
	{
		data[i] = i2c_recvbyte();
		if (i == 3)
		{

			 i2c_sendack(1);                //最后一个数据需要回NOACK
		}
		else
		{		
			 i2c_sendack(0);                //回应ACK

		}
	}
	
	i2c_stop();                          //停止信号
	delay_ms(5);
	
	
	dis_data = data[0];
	dis_data = (dis_data << 8) + data[1];//合成数据 
	
	tmp = (float)dis_data / 1.2;
		
	return tmp;
}

//void conversion(unsigned int temp_data)  //  数据转换出 个，十，百，千，万
//{  
//	wan = temp_data / 1000000 + 0x30 ;
//	temp_data = temp_data % 1000000;   //取余运算
//	qian = temp_data /100000 + 0x30 ;
//	temp_data=temp_data % 100000;    //取余运算
//	bai = temp_data /10000 + 0x30   ;
//	temp_data = temp_data % 10000;     //取余运算
//	shi = temp_data / 1000 + 0x30    ;
//	temp_data = temp_data % 1000;      //取余运算
//	ge = temp_data / 100 + 0x30; 	
//	temp_data = temp_data % 100;      //取余运算
//	fen = temp_data / 10 + 0x30;
//	temp_data = temp_data % 10;
//	miao = temp_data + 0x30;
//	
//}

