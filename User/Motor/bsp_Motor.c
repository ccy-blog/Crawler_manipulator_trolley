#include "bsp_Motor.h"


uint32_t Motor_PWM = 1000;	// ���ռ�ձ� Motor_PWM / 1000

void MOTOR_GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_GPIO_CLK , ENABLE);
	
	// ���ø�����Ϊ�����������, ��� TIM3 TIM4 CH3 CH4 PWM ���岨��  
	GPIO_InitStructure.GPIO_Pin = MOTOR_GPIO_PIN1 | MOTOR_GPIO_PIN2 | MOTOR_GPIO_PIN3 | MOTOR_GPIO_PIN4; 	//TIM3_CH3 //TIM3_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		// �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void MOTOR_PWM1_Config(uint16_t ARR,uint16_t PSC){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	MOTOR_TIMx_1_APBxClock_FUN(MOTOR_TIMx_1_CLK , ENABLE);
	
/*--------------------ʱ���ṹ���ʼ��-------------------------*/	
	TIM_TimeBaseStructure.TIM_Prescaler = PSC;						// ����CNT��������ʱ�� = Fck_int/(psc+1)
	
	TIM_TimeBaseStructure.TIM_Period = ARR;							// �Զ���װ�ؼĴ�����ֵ 
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	// ���ϼ���
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		// ����ʱ�ӷָ�: TDTS = Tck_tim

	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					// �ظ������Ĵ���
	
	TIM_TimeBaseInit(MOTOR_TIMx_1, &TIM_TimeBaseStructure); 		// ��ʼ�� TIMx

	TIM_ARRPreloadConfig(MOTOR_TIMx_1, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
	
/*--------------------����ȽϽṹ���ʼ��-------------------*/			
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;					// �������ģʽ������ΪPWMģʽ1
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		// ���ʹ��
	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	// �����������
	
	TIM_OCInitStructure.TIM_Pulse = 0; 									// ����ռ�ձȴ�С
	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			// �߼������
	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 		// ���û������������
	
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; 		// ���ͨ�����м���״̬
	
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;		// �������ͨ�����м���״̬
	
	TIM_OC3Init(MOTOR_TIMx_1, &TIM_OCInitStructure); 			// ��ʼ������ TIMx	
	TIM_OC3PreloadConfig(MOTOR_TIMx_1, TIM_OCPreload_Enable); 	// CH3 Ԥװ��ʹ��
	
	TIM_OC4Init(MOTOR_TIMx_1, &TIM_OCInitStructure); 			// ��ʼ������ TIMx	
	TIM_OC4PreloadConfig(MOTOR_TIMx_1, TIM_OCPreload_Enable); 	// CH4 Ԥװ��ʹ��

/*----------------------------------------------------------*/	
	TIM_Cmd(MOTOR_TIMx_1, ENABLE); // ʹ�� ������
	
	// �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
	//TIM_CtrlPWMOutputs(MOTOR_GEN_TIM,ENABLE); // MOE �����ʹ��
	
	TIM_SetAutoreload(MOTOR_TIMx_1, ARR);	// ����TIMx�Զ����ؼĴ���ֵ
	TIM_SetCompare3(MOTOR_TIMx_1, 0);		// ����TIMx����Ƚ�3�Ĵ���ֵ
	TIM_SetCompare4(MOTOR_TIMx_1, 0);		// ����TIMx����Ƚ�4�Ĵ���ֵ
}

void MOTOR_PWM2_Config(uint16_t ARR,uint16_t PSC)
{		 		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	MOTOR_TIMx_2_APBxClock_FUN(MOTOR_TIMx_2_CLK, ENABLE);
	
/*--------------------ʱ���ṹ���ʼ��-------------------------*/		
	TIM_TimeBaseStructure.TIM_Prescaler = PSC;						// ����CNT��������ʱ�� = Fck_int/(psc+1)

	TIM_TimeBaseStructure.TIM_Period = ARR;							// �Զ���װ�ؼĴ�����ֵ
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	// ���ϼ���
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		// ����ʱ�ӷָ�:TDTS = Tck_tim
	
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;				// �ظ��Ĵ���
	
	TIM_TimeBaseInit(MOTOR_TIMx_2, &TIM_TimeBaseStructure); 		// ��ʼ�� TIMx
	
	TIM_ARRPreloadConfig(MOTOR_TIMx_2, ENABLE); 					// ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���

/*--------------------����ȽϽṹ���ʼ��-------------------*/				
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// �������ģʽ������ΪPWMģʽ1
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// ���ʹ��
	
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;	// �������������
	
	TIM_OCInitStructure.TIM_Pulse = 0; 								// ����ռ�ձȴ�С

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		// �߼������
	 
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	// ���û����������

	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; 		// ���ͨ�����м���״̬
	
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;	// �������ͨ�����м���״̬
	
	TIM_OC3Init(MOTOR_TIMx_2, &TIM_OCInitStructure); 			// ��ʼ������ TIMx	
	TIM_OC3PreloadConfig(MOTOR_TIMx_2, TIM_OCPreload_Enable); 	// CH1 Ԥװ��ʹ��
	
	TIM_OC4Init(MOTOR_TIMx_2, &TIM_OCInitStructure); 			// ��ʼ������ TIMx	
	TIM_OC4PreloadConfig(MOTOR_TIMx_2, TIM_OCPreload_Enable); 	// CH1 Ԥװ��ʹ��

/*----------------------------------------------------------*/	
	TIM_Cmd(MOTOR_TIMx_2, ENABLE); 			// ʹ�� TIM4
	
	// �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
	//TIM_CtrlPWMOutputs(MOTOR_TIMx_2,ENABLE); // MOE �����ʹ��
	
	TIM_SetAutoreload(MOTOR_TIMx_2, ARR);	// ����TIMx�Զ����ؼĴ���ֵ
	TIM_SetCompare3(MOTOR_TIMx_2, 0);		// ����TIMx����Ƚ�3�Ĵ���ֵ
	TIM_SetCompare4(MOTOR_TIMx_2, 0);		// ����TIMx����Ƚ�3�Ĵ���ֵ
} 

void Motor_Init(void){

	MOTOR_GPIO_Config();
	MOTOR_PWM1_Config(1000, 5);		// ��ʼ���������Ƶ�� 72M / (5+1) / (1000 + 1) = 12KHZ
	MOTOR_PWM2_Config(1000, 5);		// ��ʼ���������Ƶ�� 72M / (5+1) / (1000 + 1) = 12KHZ
}

void SetMotorPWM1(int Motor_PWM){
	
		if(Motor_PWM < 0){
			
			MOTOR_TIMx_1_PWM1_3 = -Motor_PWM;
			MOTOR_TIMx_1_PWM1_4 = 0;
		
		}else{

			MOTOR_TIMx_1_PWM1_4 = Motor_PWM;
			MOTOR_TIMx_1_PWM1_3 = 0;
		}
}

void SetMotorPWM2(int Motor_PWM){
	
		if(Motor_PWM < 0){	
			
			MOTOR_TIMx_2_PWM2_3 = -Motor_PWM;
			MOTOR_TIMx_2_PWM2_4 = 0;
		
		}else{
			
			MOTOR_TIMx_2_PWM2_4 = Motor_PWM;
			MOTOR_TIMx_2_PWM2_3 = 0;
		}
}


