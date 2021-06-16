#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"
#include "stdio.h"	
#include "bsp_system.h" 

			
#define DEBUG_USARTx				USART1

/* DXBT18 模块 USART 宏定义 */

#define USARTx_DXBT18				USART1
#define USART_DXBT18_APBxCLKCmd		RCC_APB2PeriphClockCmd
#define USART_DXBT18_CLK			RCC_APB2Periph_USART1
#define	USART_DXBT18_BAUDRATE		115200

#define USART_DXBT18_GPIO_CLK		RCC_APB2Periph_GPIOA

#define USART_TX_DXBT18_GPIO_PORT	GPIOA
#define USART_TX_DXBT18_GPIO_PIN	GPIO_Pin_9
#define USART_RX_DXBT18_GPIO_PORT	GPIOA
#define USART_RX_DXBT18_GPIO_PIN	GPIO_Pin_10

#define USART_DXBT18_IRQ			USART1_IRQn
#define USART_DXBT18_IRQHandler		USART1_IRQHandler

/* WIFI 模块 USART 宏定义 */
#define USARTx_WIFI					USART2
#define USART_WIFI_APBxCLKCmd		RCC_APB1PeriphClockCmd
#define USART_WIFI_CLK				RCC_APB1Periph_USART2
#define	USART_WIFI_BAUDRATE			115200

#define USART_WIFI_GPIO_CLK			RCC_APB2Periph_GPIOA

#define USART_TX_WIFI_GPIO_PORT		GPIOA
#define USART_TX_WIFI_GPIO_PIN		GPIO_Pin_2
#define USART_RX_WIFI_GPIO_PORT		GPIOA
#define USART_RX_WIFI_GPIO_PIN		GPIO_Pin_3

#define USART_WIFI_IRQ				USART2_IRQn
#define USART_WIFI_IRQHandler		USART2_IRQHandler


#define USART_RECV_LEN  				200  	// 定义最大接收字节数 200


#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收


extern uint8_t recvFinish_flag;
extern uint8_t USART_DXBT18_RECV_BUF[USART_RECV_LEN];
extern uint8_t USART_WIFI_RECV_BUF[USART_RECV_LEN];



extern u16 USART_RX_STA;         		//接收状态标记	



void USART_DXBT18_Init(void);
void USART_WIFI_Init(void);
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void Usart_SendString(USART_TypeDef *pUSARTx, char *str);
void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch);
int fputc(int ch, FILE *f);

#endif



