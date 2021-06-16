#include "bsp_beep.h"


/* ������IO��ʼ�� */
void Beep_Init(void){
 
	GPIO_InitTypeDef GPIO_InitStructure;    
	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);  	// ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin  = BEEP_GPIO_PIN;  		// ������-->PB12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	// ����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	// IO���ٶ�Ϊ50MHZ
 	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);		// ���ݲ�����ʼ��PB12	
	GPIO_SetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);			// �رշ�����
}
