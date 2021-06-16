#ifndef __BSP_SERVOR_H
#define	__BSP_SERVOR_H

#include "stm32f10x.h"

/* ����˿�ʱ�� �� AFIOʱ�� */
#define SERVO_GPIO_CLK		(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB)

/* ����˿�A������ */
#define SERVO_GPIO_PORT1	GPIOA
#define SERVO_GPIO_PIN1		GPIO_Pin_8
#define	SERVO_GPIO_PIN2		GPIO_Pin_15

/* ����˿�B������ */
#define SERVO_GPIO_PORT2	GPIOB
#define SERVO_GPIO_PIN3		GPIO_Pin_3
#define	SERVO_GPIO_PIN4		GPIO_Pin_4
#define SERVO_GPIO_PIN5		GPIO_Pin_5
#define	SERVO_GPIO_PIN6		GPIO_Pin_15

/* PCM */
#define SERVO_PCM_MAX		2505		// ������PWM�������� 2.5ms �궨��


extern uint16_t Servo_PCM[9];


void Servor_Init(void);	
void Servo_Control(void);


#endif /* __GPIO_H */
