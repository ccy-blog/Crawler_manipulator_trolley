#include "bsp_system.h"
#include "bsp_usart.h"	
#include "online.h"
u8 USART_RX_BUF[USART_RECV_LEN];     

u16 USART_RX_STA=0;       //接收状态标记	  


/* 接收缓冲, 最大USART_REC_LEN个字节, 末字节为换行符 */
uint8_t USART_WIFI_RECV_BUF[USART_RECV_LEN];
uint8_t USART_DXBT18_RECV_BUF[USART_RECV_LEN];

uint8_t recvFinish_flag = 0;	// 接收完成标记


static void USART_DXBT18_NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 配置优先级分组
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_DXBT18_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// 抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// 子优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);								// 初始化VIC寄存器
}

static void USART_WIFI_NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 配置优先级分组
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ;	// 抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 子优先级 1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);								// 初始化VIC寄存器
}

static void USART_DXBT18_GPIO_Config(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART_DXBT18_GPIO_CLK, ENABLE);		// GPIOA时钟
	
	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = USART_TX_DXBT18_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(USART_TX_DXBT18_GPIO_PORT, &GPIO_InitStructure);
	
	// 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = USART_RX_DXBT18_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_DXBT18_GPIO_PORT, &GPIO_InitStructure);
}

static void USART_WIFI_GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART_WIFI_GPIO_CLK, ENABLE);	// GPIOA时钟
	
	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = USART_TX_WIFI_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_WIFI_GPIO_PORT, &GPIO_InitStructure);
   
	// 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = USART_RX_WIFI_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_WIFI_GPIO_PORT, &GPIO_InitStructure);
}

static void USART_DXBT18_Mode_Config(void){
  
	USART_InitTypeDef USART_InitStructure;
 
	USART_DXBT18_APBxCLKCmd(USART_DXBT18_CLK, ENABLE);		// 开启串口时钟

	USART_InitStructure.USART_BaudRate = USART_DXBT18_BAUDRATE;		// 串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;				// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式
	USART_Init(USARTx_DXBT18, &USART_InitStructure); 						// 初始化串口
	
	USART_ITConfig(USARTx_DXBT18, USART_IT_RXNE, ENABLE);		// 开启串口接受中断
	USART_Cmd(USARTx_DXBT18, ENABLE);                    		// 使能串口
}

static void USART_WIFI_Mode_Config(void){
  
	USART_InitTypeDef USART_InitStructure;
 
	USART_WIFI_APBxCLKCmd(USART_WIFI_CLK, ENABLE);					// 开启串口时钟

	USART_InitStructure.USART_BaudRate = USART_WIFI_BAUDRATE;		// 串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// 字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// 一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;				// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式
	USART_Init(USARTx_WIFI, &USART_InitStructure); 						// 初始化串口
	
	USART_ITConfig(USARTx_WIFI, USART_IT_RXNE, ENABLE);				// 开启串口接受中断
	USART_Cmd(USARTx_WIFI, ENABLE);                    				// 使能串口
}

void USART_DXBT18_Init(void){
	

	USART_DXBT18_NVIC_Config();
	USART_DXBT18_GPIO_Config();
	USART_DXBT18_Mode_Config();
}

void USART_WIFI_Init(void){
	
	USART_WIFI_NVIC_Config();  
	USART_WIFI_GPIO_Config(); 
	USART_WIFI_Mode_Config();
}

/*****************  发送一个字符 **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch){

	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx, ch);
	
	/* 等待发送数据寄存器为空 */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/*****************  发送字符串 **********************/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str){

	while(*str != '\0'){
		
		USART_SendData(pUSARTx, *str);
		str++;
	}
	
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/*****************  发送一个16位数据 **********************/
void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch){

	uint8_t temp_h, temp_l;
	
	/* 取出低八位 */
	temp_l = ch & 0xff;
	
	/* 取出高八位 */
	temp_h = ch >> 8;
		
	/* 发送高八位 */
	USART_SendData(pUSARTx, temp_h);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx, temp_l);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

int fputc(int ch, FILE *f){
	
	while((USART1->SR & 0X40) == 0);	// 循环发送,直到发送完毕   
    
	USART1->DR = (uint8_t) ch;      
	
	return ch;
}







