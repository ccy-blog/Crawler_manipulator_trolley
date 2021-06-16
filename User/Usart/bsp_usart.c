#include "bsp_system.h"
#include "bsp_usart.h"	
#include "online.h"
u8 USART_RX_BUF[USART_RECV_LEN];     

u16 USART_RX_STA=0;       //����״̬���	  


/* ���ջ���, ���USART_REC_LEN���ֽ�, ĩ�ֽ�Ϊ���з� */
uint8_t USART_WIFI_RECV_BUF[USART_RECV_LEN];
uint8_t USART_DXBT18_RECV_BUF[USART_RECV_LEN];

uint8_t recvFinish_flag = 0;	// ������ɱ��


static void USART_DXBT18_NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// �������ȼ�����
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_DXBT18_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// ��ռ���ȼ� 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// �����ȼ� 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);								// ��ʼ��VIC�Ĵ���
}

static void USART_WIFI_NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// �������ȼ�����
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ;	// ��ռ���ȼ� 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// �����ȼ� 1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);								// ��ʼ��VIC�Ĵ���
}

static void USART_DXBT18_GPIO_Config(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART_DXBT18_GPIO_CLK, ENABLE);		// GPIOAʱ��
	
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_TX_DXBT18_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(USART_TX_DXBT18_GPIO_PORT, &GPIO_InitStructure);
	
	// ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_RX_DXBT18_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_DXBT18_GPIO_PORT, &GPIO_InitStructure);
}

static void USART_WIFI_GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART_WIFI_GPIO_CLK, ENABLE);	// GPIOAʱ��
	
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_TX_WIFI_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_WIFI_GPIO_PORT, &GPIO_InitStructure);
   
	// ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_RX_WIFI_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_WIFI_GPIO_PORT, &GPIO_InitStructure);
}

static void USART_DXBT18_Mode_Config(void){
  
	USART_InitTypeDef USART_InitStructure;
 
	USART_DXBT18_APBxCLKCmd(USART_DXBT18_CLK, ENABLE);		// ��������ʱ��

	USART_InitStructure.USART_BaudRate = USART_DXBT18_BAUDRATE;		// ���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ
	USART_Init(USARTx_DXBT18, &USART_InitStructure); 						// ��ʼ������
	
	USART_ITConfig(USARTx_DXBT18, USART_IT_RXNE, ENABLE);		// �������ڽ����ж�
	USART_Cmd(USARTx_DXBT18, ENABLE);                    		// ʹ�ܴ���
}

static void USART_WIFI_Mode_Config(void){
  
	USART_InitTypeDef USART_InitStructure;
 
	USART_WIFI_APBxCLKCmd(USART_WIFI_CLK, ENABLE);					// ��������ʱ��

	USART_InitStructure.USART_BaudRate = USART_WIFI_BAUDRATE;		// ���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ
	USART_Init(USARTx_WIFI, &USART_InitStructure); 						// ��ʼ������
	
	USART_ITConfig(USARTx_WIFI, USART_IT_RXNE, ENABLE);				// �������ڽ����ж�
	USART_Cmd(USARTx_WIFI, ENABLE);                    				// ʹ�ܴ���
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

/*****************  ����һ���ַ� **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch){

	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx, ch);
	
	/* �ȴ��������ݼĴ���Ϊ�� */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str){

	while(*str != '\0'){
		
		USART_SendData(pUSARTx, *str);
		str++;
	}
	
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/*****************  ����һ��16λ���� **********************/
void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch){

	uint8_t temp_h, temp_l;
	
	/* ȡ���Ͱ�λ */
	temp_l = ch & 0xff;
	
	/* ȡ���߰�λ */
	temp_h = ch >> 8;
		
	/* ���͸߰�λ */
	USART_SendData(pUSARTx, temp_h);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx, temp_l);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

int fputc(int ch, FILE *f){
	
	while((USART1->SR & 0X40) == 0);	// ѭ������,ֱ���������   
    
	USART1->DR = (uint8_t) ch;      
	
	return ch;
}







