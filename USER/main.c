#include "usart.h"
#include "oled.h"
#include "led.h"
#include "key.h"
#include "bmp.h"
#include "BH1750FVI.h"
#include "stdlib.h"
unsigned char data[8];
//unsigned char miao,fen,ge,shi,bai,qian,wan;            //显示变量

#define READ_ECHO GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define TRIG PEout(5)
#define ECHO PEin(4)
int distance_Data;

void sr_init()
{
	
	GPIO_InitTypeDef GPIO_InitSTR;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitSTR.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitSTR.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitSTR.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitSTR.GPIO_OType = GPIO_OType_PP;
	GPIO_InitSTR.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_InitSTR);
	
	GPIO_InitSTR.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitSTR.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitSTR.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_InitSTR);
	
	GPIO_ResetBits(GPIOE,GPIO_PinSource5);		//push the pin into low
	
}

void get_Diatance()
{
	float distance = 0;
	unsigned int TIM = 0;
	
	TRIG = 1;
	delay_us(30);
	TRIG = 0;
	
	while(!READ_ECHO);
	TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE); 
	while(READ_ECHO);
	TIM_Cmd(TIM2, DISABLE); 
	
	TIM = TIM_GetCounter(TIM2);
	distance = 2 * TIM * 0.85;
	
	printf("distance = %f cm\n",distance);
}


void TIM2_Configuration(unsigned int arr,unsigned int psc)
{
	//Tout=((arr+1)*(psc+1))/Ft us    (Ft MHz)
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_DeInit(TIM2);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//enable the TIM2 to update interrupt 
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, DISABLE); 
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) 
	{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
	}
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	delay_init(168);
	LED_Init();	
	TIM2_Configuration(5000,8400-1);
	sr_init();
//	KEY_Init();
//	OLED_Init();
//	init_BH1750();

	while(1)
	{
		get_Diatance();
		LED0 = !LED0;
		delay_ms(500);
//		LED0 = ~LED0;
//		delay_ms(250);
//		single_write_BHB1750(0x01);  //POWER ON MODE
//		single_write_BHB1750(0x10);	
//		
//		delay_ms(180);
//		
//		temp = 10 * multiple_read_BH1750();
//		
//		if((unsigned int)temp/10 > 300)
//		{
//			LED1 = 0;
//			LED0 = 0;
//		}
//		else
//		{
//			LED0 = 1;
//			LED1 = 1;
//		}
//		
//			
////		if(KEY_Scan(0) == KEY1_PRES)
//		{
//			OLED_Clear();//清除显示
//			OLED_ShowString(0,0,"Light:        lx");
//			OLED_ShowNum(50,0,(unsigned int)temp/10,5,16);
//			OLED_ShowChar(90,0,'.');
//			OLED_ShowNum(96,0,(unsigned int)temp%10,1,16);
//	//		delay_ms(2000);
//		}
//		
//		printf("light:%f lx\n",temp/10);

//		OLED_ShowCHinese(26,6,0);		//学
//		OLED_ShowCHinese(16+26,6,1);//而
//		OLED_ShowCHinese(32+26,6,2);//知
//		OLED_ShowCHinese(48+26,6,3);//不
//		OLED_ShowCHinese(64+26,6,4);//足
//		OLED_DrawBMP(0,0,128,6,BMP2);//理工学院logo

		
	}
}



