#ifndef __BSP_LED_H
#define __BSP_LED_H	 

#include "stm32f10x.h"


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
// R-��ɫ
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LED1_GPIO_PORT    	GPIOB			            /* GPIO�˿� */
#define LED1_GPIO_PIN		GPIO_Pin_14			        /* ���ӵ�SCLʱ���ߵ�GPIO */



#define ON  0
#define OFF 1


/* ʹ�ñ�׼�Ĺ̼������IO */
#define LED1(statu)		statu ? GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN) : GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define digitalHi(port, pin)			{port->BSRR = pin;}		//���Ϊ�ߵ�ƽ		
#define digitalLo(port, pin)			{port->BRR = pin;}	 	//����͵�ƽ
#define digitalToggle(port, pin)		{port->ODR ^= pin;}		//�����ת״̬


/* �������IO�ĺ� */
#define LED1_OFF		digitalHi(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_ON			digitalLo(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT, LED1_GPIO_PIN)


void LED_Init(void);
		 				    
#endif
