#include "bsp_Motor.h"


uint32_t Motor_PWM = 1000;	// 电机占空比 Motor_PWM / 1000

void MOTOR_GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_GPIO_CLK , ENABLE);
	
	// 设置该引脚为复用输出功能, 输出 TIM3 TIM4 CH3 CH4 PWM 脉冲波形  
	GPIO_InitStructure.GPIO_Pin = MOTOR_GPIO_PIN1 | MOTOR_GPIO_PIN2 | MOTOR_GPIO_PIN3 | MOTOR_GPIO_PIN4; 	//TIM3_CH3 //TIM3_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		// 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void MOTOR_PWM1_Config(uint16_t ARR,uint16_t PSC){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	MOTOR_TIMx_1_APBxClock_FUN(MOTOR_TIMx_1_CLK , ENABLE);
	
/*--------------------时基结构体初始化-------------------------*/	
	TIM_TimeBaseStructure.TIM_Prescaler = PSC;						// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	
	TIM_TimeBaseStructure.TIM_Period = ARR;							// 自动重装载寄存器的值 
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	// 向上计数
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		// 设置时钟分割: TDTS = Tck_tim

	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;					// 重复计数寄存器
	
	TIM_TimeBaseInit(MOTOR_TIMx_1, &TIM_TimeBaseStructure); 		// 初始化 TIMx

	TIM_ARRPreloadConfig(MOTOR_TIMx_1, ENABLE); //使能 TIMx 在 ARR 上的预装载寄存器
	
/*--------------------输出比较结构体初始化-------------------*/			
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;					// 脉宽调制模式，配置为PWM模式1
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		// 输出使能
	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	// 互补输出禁用
	
	TIM_OCInitStructure.TIM_Pulse = 0; 									// 设置占空比大小
	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			// 高极性输出
	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 		// 设置互补端输出极性
	
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; 		// 输出通道空闲极性状态
	
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;		// 互补输出通道空闲极性状态
	
	TIM_OC3Init(MOTOR_TIMx_1, &TIM_OCInitStructure); 			// 初始化外设 TIMx	
	TIM_OC3PreloadConfig(MOTOR_TIMx_1, TIM_OCPreload_Enable); 	// CH3 预装载使能
	
	TIM_OC4Init(MOTOR_TIMx_1, &TIM_OCInitStructure); 			// 初始化外设 TIMx	
	TIM_OC4PreloadConfig(MOTOR_TIMx_1, TIM_OCPreload_Enable); 	// CH4 预装载使能

/*----------------------------------------------------------*/	
	TIM_Cmd(MOTOR_TIMx_1, ENABLE); // 使能 计数器
	
	// 主输出使能，当使用的是通用定时器时，这句不需要
	//TIM_CtrlPWMOutputs(MOTOR_GEN_TIM,ENABLE); // MOE 主输出使能
	
	TIM_SetAutoreload(MOTOR_TIMx_1, ARR);	// 设置TIMx自动加载寄存器值
	TIM_SetCompare3(MOTOR_TIMx_1, 0);		// 设置TIMx捕获比较3寄存器值
	TIM_SetCompare4(MOTOR_TIMx_1, 0);		// 设置TIMx捕获比较4寄存器值
}

void MOTOR_PWM2_Config(uint16_t ARR,uint16_t PSC)
{		 		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	MOTOR_TIMx_2_APBxClock_FUN(MOTOR_TIMx_2_CLK, ENABLE);
	
/*--------------------时基结构体初始化-------------------------*/		
	TIM_TimeBaseStructure.TIM_Prescaler = PSC;						// 驱动CNT计数器的时钟 = Fck_int/(psc+1)

	TIM_TimeBaseStructure.TIM_Period = ARR;							// 自动重装载寄存器的值
	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	// 向上计数
	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		// 设置时钟分割:TDTS = Tck_tim
	
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;				// 重复寄存器
	
	TIM_TimeBaseInit(MOTOR_TIMx_2, &TIM_TimeBaseStructure); 		// 初始化 TIMx
	
	TIM_ARRPreloadConfig(MOTOR_TIMx_2, ENABLE); 					// 使能 TIMx 在 ARR 上的预装载寄存器

/*--------------------输出比较结构体初始化-------------------*/				
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// 脉宽调制模式，配置为PWM模式1
	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// 输出使能
	
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;	// 互补端输出禁用
	
	TIM_OCInitStructure.TIM_Pulse = 0; 								// 设置占空比大小

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		// 高极性输出
	 
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	// 设置互补输出极性

	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; 		// 输出通道空闲极性状态
	
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;	// 互补输出通道空闲极性状态
	
	TIM_OC3Init(MOTOR_TIMx_2, &TIM_OCInitStructure); 			// 初始化外设 TIMx	
	TIM_OC3PreloadConfig(MOTOR_TIMx_2, TIM_OCPreload_Enable); 	// CH1 预装载使能
	
	TIM_OC4Init(MOTOR_TIMx_2, &TIM_OCInitStructure); 			// 初始化外设 TIMx	
	TIM_OC4PreloadConfig(MOTOR_TIMx_2, TIM_OCPreload_Enable); 	// CH1 预装载使能

/*----------------------------------------------------------*/	
	TIM_Cmd(MOTOR_TIMx_2, ENABLE); 			// 使能 TIM4
	
	// 主输出使能，当使用的是通用定时器时，这句不需要
	//TIM_CtrlPWMOutputs(MOTOR_TIMx_2,ENABLE); // MOE 主输出使能
	
	TIM_SetAutoreload(MOTOR_TIMx_2, ARR);	// 设置TIMx自动加载寄存器值
	TIM_SetCompare3(MOTOR_TIMx_2, 0);		// 设置TIMx捕获比较3寄存器值
	TIM_SetCompare4(MOTOR_TIMx_2, 0);		// 设置TIMx捕获比较3寄存器值
} 

void Motor_Init(void){

	MOTOR_GPIO_Config();
	MOTOR_PWM1_Config(1000, 5);		// 初始化电机工作频率 72M / (5+1) / (1000 + 1) = 12KHZ
	MOTOR_PWM2_Config(1000, 5);		// 初始化电机工作频率 72M / (5+1) / (1000 + 1) = 12KHZ
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


