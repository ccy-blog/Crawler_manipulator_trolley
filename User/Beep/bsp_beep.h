#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#include "stm32f10x.h"


/* 定义蜂鸣器连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的蜂鸣器引脚 */
#define BEEP_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define BEEP_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define BEEP_GPIO_PIN		GPIO_Pin_13	


/* 高电平时，蜂鸣器响 */
#define ON  0   
#define OFF 1


/* 带参宏，可以像内联函数一样使用 */
#define BEEP(statu)		statu ? GPIO_SetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN) : GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN)

								
// #define	Beep PBout(13)  //对PB12口输出操作				

void Beep_Init(void);

#endif
