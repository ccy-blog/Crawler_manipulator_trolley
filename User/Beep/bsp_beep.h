#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#include "stm32f10x.h"


/* ������������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶķ��������� */
#define BEEP_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define BEEP_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define BEEP_GPIO_PIN		GPIO_Pin_13	


/* �ߵ�ƽʱ���������� */
#define ON  0   
#define OFF 1


/* ���κ꣬��������������һ��ʹ�� */
#define BEEP(statu)		statu ? GPIO_SetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN) : GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN)

								
// #define	Beep PBout(13)  //��PB12���������				

void Beep_Init(void);

#endif
