#include "bsp_GenneralTIM.h"


static void GENNERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = GENNERAL_TIM_IRQ;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENNERAL_TIM_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    GENNERAL_TIM_APBxClock_FUN(GENNERAL_TIM_CLK,ENABLE);
    
	TIM_DeInit(GENNERAL_TIM);												/* 重新启动定时器 */

	TIM_TimeBaseStructure.TIM_Prescaler = GENNERAL_TIM_Prescaler;			/* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 			/* 向上计数模式 */
    TIM_TimeBaseStructure.TIM_Period = GENNERAL_TIM_Period;		 			/* 自动重装载寄存器周期的值(计数值) */
    TIM_TimeBaseStructure.TIM_ClockDivision = GENNERAL_TIM_ClockDivision; 	/* 外部时钟采样分频 */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = GENNERAL_TIM_RepetitionCounter;	/* 重复计数器的值 */
    TIM_TimeBaseInit(GENNERAL_TIM,&TIM_TimeBaseStructure);
    TIM_ClearFlag(GENNERAL_TIM,TIM_FLAG_Update);							/* 清除溢出中断标志 */
    TIM_ITConfig(GENNERAL_TIM, TIM_IT_Update, ENABLE);						/* 开启中断触发*/   
	TIM_Cmd(GENNERAL_TIM, ENABLE);	
}


/* 定时器初始化函数 */
void GENNERAL_TIM_Init(void)
{
	 GENNERAL_TIM_NVIC_Config();
	 GENNERAL_TIM_Config();
}

/* 开启定时器函数 */
void GENNERAL_TIM_ON(void)
{	
	TIM_Cmd(GENNERAL_TIM, ENABLE);
}

/* 关闭定时器函数 */
void GENNERAL_TIM_OFF(void)
{	
	TIM_Cmd(GENNERAL_TIM, DISABLE);
}
/**************************************************************************************/

