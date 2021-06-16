#include "online.h"
#include "bsp_usart.h"
#include "string.h"
#include "bsp_Motor.h"
#include "bsp_Servo.h"
#include "stdlib.h"
#include "bsp_led.h"
#include "bsp_beep.h"


uint16_t Servo_PCM_Temp[8] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,};


/* 小车前进 */
int IsCarFront(const char *str){

	if(strncmp(str, "<BUPD>", 6) == 0 || strncmp(str, "BUPD", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车后退 */
int IsCarBack(const char *str){

	if(strncmp(str, "<BDND>", 6) == 0 || strncmp(str, "BDND", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车左转 */
int IsCarLeft(const char *str){

	if(strncmp(str, "<BLTD>", 6) == 0 || strncmp(str, "BLTD", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车右转 */
int IsCarRight(const char *str){

	if(strncmp(str, "<BRTD>", 6) == 0 || strncmp(str, "BRTD", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车加速 */
int IsCarAddSpeed(const char *str){

	if(strncmp(str, "BUAD", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车减速 */
int IsCarSlowSpeed(const char *str){

	if(strncmp(str, "BUMD", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车LED */
int IsCarLED(const char *str){

	if(strncmp(str, "BUKD", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车鸣笛 */
int IsCarBeep(const char *str){

	if(strncmp(str, "BUSD", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车停止鸣笛 */
int IsCarNoBeep(const char *str){

	if(strncmp(str, "BUSN", 4) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 小车停止 */
int IsCarStop(const char *str){

	if( strncmp(str, "<BUPU>", 6) == 0 || strncmp(str, "BRTD", 4) == 0 || \
	    strncmp(str, "<BDNU>", 6) == 0 || strncmp(str, "BDNU", 4) == 0 || \
		strncmp(str, "<BLTU>", 6) == 0 || strncmp(str, "BLTU", 4) == 0 || \
		strncmp(str, "<BRTU>", 6) == 0 || strncmp(str, "BRTU", 4) == 0 || \
		strncmp(str, "<BSTD>", 6) == 0 || strncmp(str, "BSTD", 4) == 0 ){	return 1;	
	
	}else{	return 0;	}
}

/* 舵机 0 控制 */
int IsServo0(const char *str){

	if(strncmp(str, "<SUP-", 5) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 舵机 1 控制 */
int IsServo1(const char *str){

	if(strncmp(str, "<SLT-", 5) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 舵机 2 控制 */
int IsServo2(const char *str){

	if(strncmp(str, "<SDN-", 5) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 舵机 3 控制 */
int IsServo3(const char *str){

	if(strncmp(str, "<SRT-", 5) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 舵机 4 控制 */
int IsServo4(const char *str){

	if(strncmp(str, "<SDL-", 5) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* 舵机 5 控制 */
int IsServo5(const char *str){

	if(strncmp(str, "<SDR-", 5) == 0){	return 1;	
	
	}else{	return 0;	}
}

/* Servo0 控制 */
void Servo0_Control(const char *str){

	const char *data = NULL;
	unsigned int PCM;
	
	data = strchr(str, '-');
	if(data != NULL){
	
		data++;
		PCM = atol(data);
		Servo_PCM[1] = PCM;
	}
}

/* Servo1 控制 */
void Servo1_Control(const char *str){

	const char *data = NULL;
	unsigned int PCM;
	
	data = strchr(str, '-');
	if(data != NULL){
	
		data++;
		PCM = atol(data);
		Servo_PCM[2] = PCM;
	}
}

/* Servo2 控制 */
void Servo2_Control(const char *str){

	const char *data = NULL;
	unsigned int PCM;
	
	data = strchr(str, '-');
	if(data != NULL){
	
		data++;
		PCM = atol(data);
		Servo_PCM[3] = PCM;
	}
}

/* Servo3 控制 */
void Servo3_Control(const char *str){

	const char *data = NULL;
	unsigned int PCM;
	
	data = strchr(str, '-');
	if(data != NULL){
	
		data++;
		PCM = atol(data);
		Servo_PCM[4] = PCM;
	}
}

/* Servo4 控制 */
void Servo4_Control(const char *str){

	const char *data = NULL;
	unsigned int PCM;
	
	data = strchr(str, '-');
	if(data != NULL){
	
		data++;
		PCM = atol(data);
		Servo_PCM[5] = PCM;
	}
}

/* Servo5 控制 */
void Servo5_Control(const char *str){

	const char *data = NULL;
	unsigned int PCM;
	
	data = strchr(str, '-');
	if(data != NULL){
	
		data++;
		PCM = atol(data);
		Servo_PCM[6] = PCM;
	}
}

void Servor_parse(const char *str){

	unsigned int i = 0;
	unsigned flag_num = 0;
	unsigned flag_PCM = 0;
	unsigned flag_time = 0;
	unsigned int data = 0;
	unsigned int index = 0;
	unsigned int Servo_Index = 0;
	unsigned int PCM = 0;
	unsigned int Servo_Time = 0;
	
	while(str[i] != '\n'){
	
		if(flag_num == 1){
			
			if(str[i] != 'P'){
				
				data = atol(&str[i]);
				index = index * 10 + data;
			
			}else{
			
				flag_num = 0;
			}
		
		}else if(flag_PCM == 1){
			
			if(str[i] != 'T' && str[i] != '#'){
				
				data = atol(&str[i]);
				PCM = PCM * 10 + data;
			
			}else{
			
				flag_PCM = 0;
				if(PCM > 2500){	PCM = 2500;	}
				
				Servo_PCM_Temp[index] = PCM;
				PCM = 0;
				Servo_Index = index;
				index = 0;
			}
			
		}else if(flag_time == 1){
		
			data = atol(&str[i]);
			Servo_Time = Servo_Time * 10 + data;
			Servo_PCM_Temp[0] = Servo_Time;
			if(str[i+1] == '\r'){
			
				if(Servo_Time <= 100){	Servo_PCM[Servo_Index] = Servo_PCM_Temp[Servo_Index];	}
			}
		}
		
		if(str[i] == '#'){	flag_num = 1;	
		
		}else if(str[i] == 'P'){	flag_PCM = 1;
			
		}else if(str[i] == 'T'){	flag_time = 1;	
		
		}
		
		i++;
	}
}



void APP_Control_Car(void)
{
    if(recvFinish_flag)
	{
		const char *recv_buf = (char *)USART_DXBT18_RECV_BUF;
		recvFinish_flag = 0;	
		
		if(IsCarFront(recv_buf)){
			
			SetMotorPWM1(Motor_PWM);
			SetMotorPWM2(Motor_PWM);
		
		}else if(IsCarBack(recv_buf)){
			
			SetMotorPWM1(-Motor_PWM);
			SetMotorPWM2(-Motor_PWM);
		
		}else if(IsCarLeft(recv_buf)){
			
			SetMotorPWM1(Motor_PWM);
			SetMotorPWM2(-Motor_PWM);
		
		}else if(IsCarRight(recv_buf)){
			
			SetMotorPWM1(-Motor_PWM);
			SetMotorPWM2(Motor_PWM);
			
		}else if(IsCarStop(recv_buf)){
			
			SetMotorPWM1(0);
			SetMotorPWM1(0);
			
		}else if(IsServo0(recv_buf)){
	
			Servo0_Control(recv_buf);
			
		}else if(IsServo1(recv_buf)){
			
			Servo1_Control(recv_buf);
	
		}else if(IsServo2(recv_buf)){
			
			Servo2_Control(recv_buf);
			
		}else if(IsServo3(recv_buf)){
			
			Servo3_Control(recv_buf);
			
		}else if(IsServo4(recv_buf)){
			
			Servo4_Control(recv_buf);
		
		}else if(IsServo5(recv_buf)){
			
			Servo5_Control(recv_buf);
		
		}else if(IsCarAddSpeed(recv_buf)){
			
			Motor_PWM += 100;
			if(Motor_PWM >= 1000){	Motor_PWM = 1000;	}
		
		}else if(IsCarSlowSpeed(recv_buf)){
			
			Motor_PWM -= 100;
			if(Motor_PWM <= 700){	Motor_PWM = 700;	}
		
		}else if(IsCarLED(recv_buf)){
			
			LED1_TOGGLE;
		
		}else if(IsCarBeep(recv_buf)){
			
			BEEP(ON);
		
		}else if(IsCarNoBeep(recv_buf)){
			
			BEEP(OFF);
		
		}else{
		
			Servor_parse(recv_buf);
		}
	}
}
