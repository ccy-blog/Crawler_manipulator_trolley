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
    
	TIM_DeInit(GENNERAL_TIM);												/* ����������ʱ�� */

	TIM_TimeBaseStructure.TIM_Prescaler = GENNERAL_TIM_Prescaler;			/* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 			/* ���ϼ���ģʽ */
    TIM_TimeBaseStructure.TIM_Period = GENNERAL_TIM_Period;		 			/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    TIM_TimeBaseStructure.TIM_ClockDivision = GENNERAL_TIM_ClockDivision; 	/* �ⲿʱ�Ӳ�����Ƶ */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = GENNERAL_TIM_RepetitionCounter;	/* �ظ���������ֵ */
    TIM_TimeBaseInit(GENNERAL_TIM,&TIM_TimeBaseStructure);
    TIM_ClearFlag(GENNERAL_TIM,TIM_FLAG_Update);							/* �������жϱ�־ */
    TIM_ITConfig(GENNERAL_TIM, TIM_IT_Update, ENABLE);						/* �����жϴ���*/   
	TIM_Cmd(GENNERAL_TIM, ENABLE);	
}


/* ��ʱ����ʼ������ */
void GENNERAL_TIM_Init(void)
{
	 GENNERAL_TIM_NVIC_Config();
	 GENNERAL_TIM_Config();
}

/* ������ʱ������ */
void GENNERAL_TIM_ON(void)
{	
	TIM_Cmd(GENNERAL_TIM, ENABLE);
}

/* �رն�ʱ������ */
void GENNERAL_TIM_OFF(void)
{	
	TIM_Cmd(GENNERAL_TIM, DISABLE);
}
/**************************************************************************************/

