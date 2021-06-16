#include "bsp_SysTick.h"


static __IO u32 TimingDelay;

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms 中断一次
	 * SystemFrequency / 100000	 10us 中断一次
	 * SystemFrequency / 1000000 1us 中断一次
	 */
//	if(SysTick_Config(SystemFrequency / 1000))	// ST3.0.0库版本
	if(SysTick_Config(SystemCoreClock / 1000)){	// ST3.5.0库版本
	 
		while (1);
	}
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief   ms延时程序,10us为一个单位
  * @param  
  *		@arg nTime: Delay_ms( 1 ) 则实现的延时为 1 * 1ms = 1ms
  * @retval  无
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


// couter 减1的时间 等于 1/systick_clk
// 当counter 从 reload 的值减小到0的时候，为一个循环，如果开启了中断则执行中断服务程序，
// 同时 CTRL 的 countflag 位会置1
// 这一个循环的时间为 reload * (1/systick_clk)
void SysTick_Delay_Us(__IO uint32_t us){

	uint32_t i;
	
	SysTick_Config(SystemCoreClock / 1000000);
	
	for(i = 0; i < us; i++){
	
		// 当计数器的值减小到0的时候，CRTL寄存器的位16会置1
		// 当置1时，读取该位会清0
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	// 关闭SysTick定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_Ms(__IO uint32_t ms){

	uint32_t i;
	
	SysTick_Config(SystemCoreClock / 1000);
	
	for(i = 0; i < ms; i++){
	
		// 当计数器的值减小到0的时候，CRTL寄存器的位16会置1
		// 当置1时，读取该位会清0
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	// 关闭SysTick定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
