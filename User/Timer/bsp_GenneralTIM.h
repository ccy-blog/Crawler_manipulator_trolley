#ifndef __BSP_GENNERALTIM_H
#define __BSP_GENNERALTIM_H

#include "stm32f10x.h"
 
#define GENNERAL_TIM2	

#ifdef 	GENNERAL_TIM2	
#define GENNERAL_TIM					TIM2
#define GENNERAL_TIM_APBxClock_FUN		RCC_APB1PeriphClockCmd
#define GENNERAL_TIM_CLK				RCC_APB1Periph_TIM2
#define GENNERAL_TIM_Prescaler			(72 - 1)
#define GENNERAL_TIM_ClockDivision		TIM_CKD_DIV1
#define GENNERAL_TIM_RepetitionCounter	0
#define GENNERAL_TIM_Period				(2505 - 1)
#define GENNERAL_TIM_IRQ				TIM2_IRQn
#define GENNERAL_TIM_IRQHandler			TIM2_IRQHandler

#endif
 
 
 
void GENNERAL_TIM_Init(void);
void GENNERAL_TIM_ON(void);
void GENNERAL_TIM_OFF(void);

#endif	
