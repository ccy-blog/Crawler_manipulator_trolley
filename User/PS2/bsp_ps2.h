#ifndef __BSP_PS2_H__
#define __BSP_PS2_H__

#include "bsp_SysTick.h"
#include "stm32f10x.h"
#include "bsp_system.h"


#define PS2_GPIO_CLK		RCC_APB2Periph_GPIOA
#define PS2_GPIO_PORT		GPIOA
#define PS2_CLK_GPIO_PIN	GPIO_Pin_11		
#define PS2_ATT_GPIO_PIN	GPIO_Pin_12	
#define PS2_CMD_GPIO_PIN	GPIO_Pin_13	
#define PS2_DAT_GPIO_PIN	GPIO_Pin_14		

#define DI		PAin(14)		// PA14  输入
#define DO_H	PAin(13) = 1	// 命令位高
#define DO_L	PAin(13) = 0	// 命令位低
#define CS_H	PAin(12) = 1	// CS拉高
#define CS_L	PAin(12) = 0	// CS拉低
#define CLK_H	PAin(11) = 1	// 时钟拉高
#define CLK_L	PAin(11) = 0	// 时钟拉低

/* 按键宏定义 */
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE		16
#define PSB_GREEN       PSB_TRIANGLE
#define PSB_RED         PSB_CIRCLE
#define PSB_BLUE        PSB_CROSS
#define PSB_PINK        PSB_SQUARE

/* 摇杆宏定义 */
#define PSS_RX		5
#define PSS_RY		6
#define PSS_LX		7
#define PSS_LY		8

/* PS2 Mode */
#define PS2_MODE_GREEN		1
#define PS2_MODE_RED		0

extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Init(void);
void PS2_Cmd(uint8_t CMD);
void PS2_ReadHandleData(void);
uint8_t PS2_GetKey(void);		
uint8_t PS2_GetMode(void);
uint8_t PS2_GetRockerAnologData(uint8_t button); 
void PS2_ClearHandleData(void);	 
void PS2_Control_Car(void);

#endif
