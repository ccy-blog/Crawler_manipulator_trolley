#include "bsp_led.h"


 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_Init(void){
 
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK,ENABLE);		// ʹ��PA�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin  = LED1_GPIO_PIN;     	// LED-->PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	// ����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	// IO���ٶ�Ϊ50MHZ
 	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);		// ��ʼ��PB14	
	GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);			// PB.14 �����

	/* �ر�led�� */
	LED1_OFF;
}

void assert_failed(uint8_t *file, uint32_t line){

	// ���Դ���ʱִ�еĴ���
	LED1_ON;
}


