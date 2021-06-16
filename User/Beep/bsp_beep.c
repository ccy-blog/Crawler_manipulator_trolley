#include "bsp_beep.h"


/* 蜂鸣器IO初始化 */
void Beep_Init(void){
 
	GPIO_InitTypeDef GPIO_InitStructure;    
	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);  	// 使能PB端口时钟
	GPIO_InitStructure.GPIO_Pin  = BEEP_GPIO_PIN;  		// 蜂鸣器-->PB12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	// 设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	// IO口速度为50MHZ
 	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);		// 根据参数初始化PB12	
	GPIO_SetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);			// 关闭蜂鸣器
}
