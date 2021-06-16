#include "bsp_SysTick.h"


static __IO u32 TimingDelay;

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms �ж�һ��
	 * SystemFrequency / 100000	 10us �ж�һ��
	 * SystemFrequency / 1000000 1us �ж�һ��
	 */
//	if(SysTick_Config(SystemFrequency / 1000))	// ST3.0.0��汾
	if(SysTick_Config(SystemCoreClock / 1000)){	// ST3.5.0��汾
	 
		while (1);
	}
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief   ms��ʱ����,10usΪһ����λ
  * @param  
  *		@arg nTime: Delay_ms( 1 ) ��ʵ�ֵ���ʱΪ 1 * 1ms = 1ms
  * @retval  ��
  */
void Delay_ms(u32 mTime)           
{ 
	TimingDelay = mTime;	
  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}


// couter ��1��ʱ�� ���� 1/systick_clk
// ��counter �� reload ��ֵ��С��0��ʱ��Ϊһ��ѭ��������������ж���ִ���жϷ������
// ͬʱ CTRL �� countflag λ����1
// ��һ��ѭ����ʱ��Ϊ reload * (1/systick_clk)
void SysTick_Delay_Us(__IO uint32_t us){

	uint32_t i;
	
	SysTick_Config(SystemCoreClock / 1000000);
	
	for(i = 0; i < us; i++){
	
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
		// ����1ʱ����ȡ��λ����0
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	// �ر�SysTick��ʱ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_Ms(__IO uint32_t ms){

	uint32_t i;
	
	SysTick_Config(SystemCoreClock / 1000);
	
	for(i = 0; i < ms; i++){
	
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
		// ����1ʱ����ȡ��λ����0
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	// �ر�SysTick��ʱ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
