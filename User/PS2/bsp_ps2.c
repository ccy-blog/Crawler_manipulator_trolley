#include "bsp_ps2.h"
#include "bsp_usart.h"
#include "bsp_Motor.h"
#include "bsp_Servo.h"
//#include "stm32f10x_pwr.h"

/*********************************************************
File��PS2��������
Description: PS2��������
**********************************************************/	 

uint16_t KeyData;
uint8_t Command[2] = {0x01,0x42};	// ��ʼ����, ��������
uint8_t HandleData[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //���ݴ洢����
uint16_t Keys[] = {
	
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
};

int LX_AD = 0;
int LY_AD = 0;
int RX_AD = 0;
int RY_AD = 0;
uint32_t key, key_bak;
uint8_t ps2_mode = 0;


void PS2_Init(void){
	
    //����  DI->PA14   		
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(PS2_GPIO_CLK, ENABLE);	
	
/* ---------------------PS2 GPIO ���� ����------------------------ */	
	GPIO_InitStructure.GPIO_Pin  = PS2_DAT_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	// ��������
	//PWR_BackupAccessCmd(ENABLE);
	//RCC_LSEConfig(RCC_LSE_OFF);
	//BKP_TamperPinCmd(DISABLE);
	//PWR_BackupAccessCmd(DISABLE);
 	GPIO_Init(PS2_GPIO_PORT, &GPIO_InitStructure);
	
   
/* ---------------------PS2 GPIO ��� ����--------------------- */	
	GPIO_InitStructure.GPIO_Pin = PS2_CLK_GPIO_PIN | PS2_ATT_GPIO_PIN | PS2_CMD_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PS2_GPIO_PORT, &GPIO_InitStructure); 	
}


// ���ֱ���������
void PS2_Cmd(uint8_t CMD){
	
	volatile uint16_t bit_x = 0x01;
	HandleData[1] = 0;
	
	/* ���ֱ����� ID ��ͬʱ������������ 0x42����������*/
	for(bit_x = 0x01; bit_x < 0x100; bit_x <<= 1)
	{
		if(bit_x & CMD){	DO_H;                 
		
		}else{	DO_L;	}
		
		/* ���ݴ�����ʱ�ӵ��½��� */
		CLK_H;
		SysTick_Delay_Us(50);
		CLK_L;
		SysTick_Delay_Us(50);
		CLK_H;		// ʱ���������
		
		if(DI){	HandleData[1] |= bit_x;	}
	}
}

/* ��ȡ�ֱ�ģʽ */
uint8_t PS2_GetMode(void){
	
	CS_L;
	PS2_Cmd(Command[0]);  //��ʼ����
	PS2_Cmd(Command[1]);  //��������
	CS_H;
	
	if(HandleData[1] == 0X73){   return 0 ;		// ���ģʽ
	
	}else if(HandleData[1] == 0X41){	return 1;	// �̵�ģʽ
	
	}else{	return 2;	}
}

/* ��ȡ�ֱ����͹��������� */
void PS2_ReadHandleData(void){
	
	volatile uint8_t index = 0;
	volatile uint16_t bit_x = 0x01;

	CS_L;

	PS2_Cmd(Command[0]);  //��ʼ����
	PS2_Cmd(Command[1]);  //��������

	/* ��ʼ����7���ֽ����� */
	for(index = 2; index < 9; index++)          
	{
		for(bit_x = 0x01; bit_x < 0x100; bit_x <<= 1)
		{
			CLK_H;
			CLK_L;
			SysTick_Delay_Us(50);
			CLK_H;
		    if(DI){	HandleData[index] |= bit_x;	}
		}
		SysTick_Delay_Us(50);
	}
	CS_H;	
}

/* ������ݻ����� */
void PS2_ClearHandleData(void){
	
	uint8_t i;
	for(i = 0; i < 9; i++){
		
		HandleData[i] = 0x00;
	}
}

// �Զ�������PS2�����ݽ��д���      ֻ�����˰�������         Ĭ�������Ǻ��ģʽ  ֻ��һ����������ʱ
// ����Ϊ0�� δ����Ϊ1
uint8_t PS2_GetKey(void){
	
	uint8_t key_x;
	
	PS2_ClearHandleData();
	PS2_ReadHandleData();

	KeyData = (HandleData[4] << 8) | HandleData[3];     // 16������, ����Ϊ 0, δ����Ϊ 1 
	for(key_x = 0; key_x < 16; key_x++){
	    
		if((KeyData & (1 << (Keys[key_x] - 1))) == 0){
			
			return key_x + 1;
		}	
	}
	return 0;          //û���κΰ�������
}

/* �õ�һ��ҡ�˵�ģ����	 ��Χ0~255 */
uint8_t PS2_GetRockerAnologData(uint8_t button){
	
	return HandleData[button];
}

void PS2_Control_Car(void){
	
	Delay_ms(85);
	
	key = PS2_GetKey(); 
	LY_AD = PS2_GetRockerAnologData(PSS_LY);
	RY_AD = PS2_GetRockerAnologData(PSS_RY);	
	ps2_mode = PS2_GetMode();
	if(ps2_mode == PS2_MODE_RED){
		
		if(key == PSB_PAD_UP){
			
			Servo_PCM[2] -= 25;
			if(Servo_PCM[2] <= 800){	Servo_PCM[2] = 800;	}
		
		}else if(key == PSB_PAD_DOWN){
			
			Servo_PCM[2] += 25;
			if(Servo_PCM[1] >= 2200){	Servo_PCM[2] = 2200;	}
		
		}else if(key == PSB_PAD_LEFT){
			
			Servo_PCM[1] += 25;
			if(Servo_PCM[1] >= 2200){	Servo_PCM[1] = 2200;	}
		
		}else if(key == PSB_PAD_RIGHT){
			
			Servo_PCM[1] -= 25;
			if(Servo_PCM[1] <= 800){	Servo_PCM[1] = 800;	}
		
		}else if(key == PSB_TRIANGLE){
			
			Servo_PCM[3] += 25;
			if(Servo_PCM[3] >= 2200){	Servo_PCM[3] = 2200;	}
		
		}else if(key == PSB_CROSS){
			
			Servo_PCM[3] -= 25;
			if(Servo_PCM[3] <= 800){	Servo_PCM[3] = 800;	}
		
		}else if(key == PSB_PINK){
			
			Servo_PCM[4] += 25;
			if(Servo_PCM[4] >= 2200){	Servo_PCM[4] = 2200;	}
		
		}else if(key == PSB_CIRCLE){
			
			Servo_PCM[4] -= 25;
			if(Servo_PCM[4] <= 800){	Servo_PCM[4] = 800;	}
		
		}else if(key == PSB_L1){
			
			Servo_PCM[5] += 25;
			if(Servo_PCM[5] >= 2200){	Servo_PCM[5] = 2200;	}
		
		}else if(key == PSB_L2){
			
			Servo_PCM[5] -= 25;
			if(Servo_PCM[5] <= 800){	Servo_PCM[5] = 800;	}
		
		}else if(key == PSB_R1){
			
			Servo_PCM[6] += 25;
			if(Servo_PCM[6] >= 2200){	Servo_PCM[6] = 2200;	}
		
		}else if(key == PSB_R2){
			
			Servo_PCM[6] -= 25;
			if(Servo_PCM[6] <= 800){	Servo_PCM[6] = 800;	}
		}

		
		/* PWM2 ������� */
		if(LY_AD > 110 && LY_AD <= 146){	// ����ֹͣ
			
			SetMotorPWM2(0);
		
		}else if(LY_AD >= 0 && LY_AD <= 110){	// ���ֺ���
			
			SetMotorPWM2(Motor_PWM);
		
		}else if(LY_AD>146 && LY_AD<=255){	// ����ǰ��
			
			SetMotorPWM2(-Motor_PWM);
		}
		
		if(RY_AD > 110 && RY_AD <= 146){	// ����ֹͣ
			
			SetMotorPWM1(0);
		
		}else if(RY_AD >= 0 && RY_AD <= 110){	// ���ֺ���
			
			SetMotorPWM1(Motor_PWM);
		
		}else if(RY_AD > 146 && RY_AD <= 255){	// ����ǰ��
			
			SetMotorPWM1(-Motor_PWM);
		}						
	}
}






