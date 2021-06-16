#include "bsp_Servo.h"
#include "bsp_GenneralTIM.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"


/* 舵机的控制一般需要一个20ms左右的时基脉冲 
 * 20ms / 8 = 2.5 ms  所以舵机一个周期最小为 2.5ms
 * 0.5ms————-0度；

 * 1.0ms————45度；

 * 1.5ms————90度；

 * 2.0ms———–135度；

 * 2.5ms———–180度；
 
*/

uint16_t Servo_PCM[9] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
uint8_t Servo_2Count = 1;				 // 每个变量用作8路舵机先后赋值控制
unsigned int led_time = 0;

extern uint8_t flag_vpwm;
#define	LED PBout(14) 

extern unsigned char flag_scan_ps2;
u8 time=0;


void Servor_Init(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(SERVO_GPIO_CLK, ENABLE);		// 开启时钟
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出
	
/* --------------Servo GPIO端口A 配置 ------------*/
	GPIO_InitStructure.GPIO_Pin =  SERVO_GPIO_PIN1 | SERVO_GPIO_PIN2;
	GPIO_Init(SERVO_GPIO_PORT1, &GPIO_InitStructure);

/* --------------Servo GPIO端口A 配置 ------------*/	
	GPIO_InitStructure.GPIO_Pin =  SERVO_GPIO_PIN3 | SERVO_GPIO_PIN4 | SERVO_GPIO_PIN5 | SERVO_GPIO_PIN6;
	GPIO_Init(SERVO_GPIO_PORT2, &GPIO_InitStructure);	
}

/* 舵机控制 */
void Servo_Control(void){
	
	if(Servo_2Count == 1){
		
		GENNERAL_TIM->ARR = Servo_PCM[1];					// 设置 ARR 的值, 使得舵机占空比为 ARR / 1M
		GPIO_SetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN6);	// 电平反转

	}else if(Servo_2Count == 2){
		
		GENNERAL_TIM->ARR = SERVO_PCM_MAX - Servo_PCM[1]; 
		GPIO_ResetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN6); 
		
	}else if(Servo_2Count == 3){
		
		GENNERAL_TIM->ARR = Servo_PCM[2]; 
		GPIO_SetBits(SERVO_GPIO_PORT1, SERVO_GPIO_PIN1); 
		
	}else if(Servo_2Count == 4){
		
		GENNERAL_TIM->ARR = SERVO_PCM_MAX - Servo_PCM[2];  
		GPIO_ResetBits(SERVO_GPIO_PORT1, SERVO_GPIO_PIN1); 
		
	}else if(Servo_2Count == 5){
		
		GENNERAL_TIM->ARR = Servo_PCM[3];  
		GPIO_SetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN5); 
		
	}else if(Servo_2Count == 6){
		
		GENNERAL_TIM->ARR = SERVO_PCM_MAX - Servo_PCM[3];  
		GPIO_ResetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN5);
		
	}else if(Servo_2Count == 7){
		
		GENNERAL_TIM->ARR = Servo_PCM[4];  
		GPIO_SetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN4); 
		
	}else if(Servo_2Count == 8){
		
		GENNERAL_TIM->ARR = SERVO_PCM_MAX - Servo_PCM[4];  
		GPIO_ResetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN4);
		
	}else if(Servo_2Count == 9){
		
		GENNERAL_TIM->ARR = Servo_PCM[5];  
		GPIO_SetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN3); 
		
	}else if(Servo_2Count == 10){
		
		GENNERAL_TIM->ARR = SERVO_PCM_MAX - Servo_PCM[5];  
		GPIO_ResetBits(SERVO_GPIO_PORT2, SERVO_GPIO_PIN3);
		
	}else if(Servo_2Count == 11){
		
		GENNERAL_TIM->ARR = Servo_PCM[6];  
		GPIO_SetBits(SERVO_GPIO_PORT1, SERVO_GPIO_PIN6); 
		
	}else if(Servo_2Count == 12){
		
		GENNERAL_TIM->ARR = SERVO_PCM_MAX - Servo_PCM[6];  
		GPIO_ResetBits(SERVO_GPIO_PORT1, SERVO_GPIO_PIN6);		
		
	}else if(Servo_2Count == 13){
		
		GENNERAL_TIM->ARR = Servo_PCM[7];  
		
	}else if(Servo_2Count == 14){
		
		GENNERAL_TIM->ARR = SERVO_PCM_MAX - Servo_PCM[7];  
		
	}else if(Servo_2Count == 15){
		
		GENNERAL_TIM->ARR = Servo_PCM[8];  
		
	}else if(Servo_2Count == 16){
		
		GENNERAL_TIM->ARR=SERVO_PCM_MAX - Servo_PCM[8]; 
		
		led_time++;
		if(led_time == 25){	
			
			led_time = 0;
			LED1_TOGGLE;	
		}
		Servo_2Count = 0;
	}
	Servo_2Count++;
}




