#ifndef __BSP_LED_H
#define __BSP_LED_H	 

#include "stm32f10x.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// R-红色
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED1_GPIO_PORT    	GPIOB			            /* GPIO端口 */
#define LED1_GPIO_PIN		GPIO_Pin_14			        /* 连接到SCL时钟线的GPIO */



#define ON  0
#define OFF 1


/* 使用标准的固件库控制IO */
#define LED1(statu)		statu ? GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN) : GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)

/* 直接操作寄存器的方法控制IO */
#define digitalHi(port, pin)			{port->BSRR = pin;}		//输出为高电平		
#define digitalLo(port, pin)			{port->BRR = pin;}	 	//输出低电平
#define digitalToggle(port, pin)		{port->ODR ^= pin;}		//输出反转状态


/* 定义控制IO的宏 */
#define LED1_OFF		digitalHi(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_ON			digitalLo(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT, LED1_GPIO_PIN)


void LED_Init(void);
		 				    
#endif
