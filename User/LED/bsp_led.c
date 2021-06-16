#include "bsp_led.h"


 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_Init(void){
 
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK,ENABLE);		// 使能PA端口时钟
	GPIO_InitStructure.GPIO_Pin  = LED1_GPIO_PIN;     	// LED-->PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	// 设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	// IO口速度为50MHZ
 	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);		// 初始化PB14	
	GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);			// PB.14 输出高

	/* 关闭led灯 */
	LED1_OFF;
}

void assert_failed(uint8_t *file, uint32_t line){

	// 断言错误时执行的代码
	LED1_ON;
}


