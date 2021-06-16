#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include <stdlib.h>
#include <string.h>					
#include "bsp_usart.h"		  					//包含串口通信设置头文件
#include "bsp_SysTick.h"						//包含系统定时器库头文件
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_GenneralTIM.h"
#include "bsp_Motor.h"
#include "bsp_Servo.h"
#include "online.h"
#include "bsp_ps2.h"


//extern uint16 Servo_PCM[9];

unsigned int dj1=1500;
unsigned int dj2=1500;
unsigned int dj3=1500;
unsigned int dj4=1500;
unsigned int dj5=1500;
unsigned int dj6=1600;
 char buf[30];


unsigned char i=0;

uint8_t flag_vpwm=0;


int ps2_count=0;
u32 systick_ms;


int main(void)
{   	
	LED_Init();	      
	Beep_Init();
	Servor_Init();
	GENNERAL_TIM_Init();
	PS2_Init();
	Motor_Init();

	USART_DXBT18_Init();
	USART_WIFI_Init();
	
	while (1)
	{	
		APP_Control_Car();
		PS2_Control_Car();
	}
} 


	

