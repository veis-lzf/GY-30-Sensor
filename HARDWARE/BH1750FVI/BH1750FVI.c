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
	i2c_start();                          //��ʼ�ź�
	i2c_sendbyte(SlaveAddress + WRITE);           //�����豸��ַ+д�ź�
	i2c_sendbyte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
	i2c_stop();
	
	delay_us(5);
	
	i2c_start();                          //��ʼ�ź�
	i2c_sendbyte(SlaveAddress + READ);         //�����豸��ַ+���ź�
	REG_data=i2c_recvbyte();              //�����Ĵ�������
	i2c_sendack(0);   
	i2c_stop();                           //ֹͣ�ź�
	
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

			 i2c_sendack(1);                //���һ��������Ҫ��NOACK
		}
		else
		{		
			 i2c_sendack(0);                //��ӦACK

		}
	}
	
	i2c_stop();                          //ֹͣ�ź�
	delay_ms(5);
	
	
	dis_data = data[0];
	dis_data = (dis_data << 8) + data[1];//�ϳ����� 
	
	tmp = (float)dis_data / 1.2;
		
	return tmp;
}

//void conversion(unsigned int temp_data)  //  ����ת���� ����ʮ���٣�ǧ����
//{  
//	wan = temp_data / 1000000 + 0x30 ;
//	temp_data = temp_data % 1000000;   //ȡ������
//	qian = temp_data /100000 + 0x30 ;
//	temp_data=temp_data % 100000;    //ȡ������
//	bai = temp_data /10000 + 0x30   ;
//	temp_data = temp_data % 10000;     //ȡ������
//	shi = temp_data / 1000 + 0x30    ;
//	temp_data = temp_data % 1000;      //ȡ������
//	ge = temp_data / 100 + 0x30; 	
//	temp_data = temp_data % 100;      //ȡ������
//	fen = temp_data / 10 + 0x30;
//	temp_data = temp_data % 10;
//	miao = temp_data + 0x30;
//	
//}

