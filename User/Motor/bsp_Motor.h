#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__
//#include "sys.h"
#include "stm32f10x.h"

/* Motor GPIO 宏定义 */
#define MOTOR_GPIO_CLK		(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB)
#define MOTOR_GPIO_PORT		GPIOB
#define MOTOR_GPIO_PIN1		GPIO_Pin_0
#define MOTOR_GPIO_PIN2		GPIO_Pin_1
#define MOTOR_GPIO_PIN3		GPIO_Pin_8
#define MOTOR_GPIO_PIN4		GPIO_Pin_9

/* Motor TIM3 宏定义 */
#define MOTOR_TIMx_1					TIM3
#define MOTOR_TIMx_1_APBxClock_FUN		RCC_APB1PeriphClockCmd
#define MOTOR_TIMx_1_CLK				RCC_APB1Periph_TIM3

/* Motor TIM4 宏定义 */
#define MOTOR_TIMx_2					TIM4
#define MOTOR_TIMx_2_APBxClock_FUN		RCC_APB1PeriphClockCmd
#define MOTOR_TIMx_2_CLK				RCC_APB1Periph_TIM4


#define MOTOR_TIMx_1_PWM1_3			TIM3->CCR3  //PB0
#define MOTOR_TIMx_1_PWM1_4			TIM3->CCR4  //PB1
#define MOTOR_TIMx_2_PWM2_3			TIM4->CCR4  //PB8
#define MOTOR_TIMx_2_PWM2_4			TIM4->CCR3  //PB9


extern uint32_t Motor_PWM;


void Motor_Init(void);
void SetMotorPWM1(int Motor_PWM);
void SetMotorPWM2(int Motor_PWM);

#endif
