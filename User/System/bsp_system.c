#include "bsp_system.h"


/* �������´���,֧��printf����,������Ҫѡ��use MicroLIB	*/
#pragma import(__use_no_semihosting)             
/* ��׼����Ҫ��֧�ֺ��� */                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       

/*����_sys_exit()�Ա���ʹ�ð�����ģʽ  */  
_sys_exit(int x) 
{ 
	x = x; 
} 


// THUMBָ�֧�ֻ������

/* ִ��WFIָ�� */
void WFI_SET(void){
	
	__ASM volatile("wfi");		  
}

/* �ر������ж� */
void INTX_DISABLE(void){
	
	__ASM volatile("cpsid i");
}

/* ���������ж� */
void INTX_ENABLE(void){
	
	__ASM volatile("cpsie i");		  
}

/* ���ö�ջ��ַ */
//addr:ջ����ַ
__asm void MSR_MSP(uint32_t addr){
	
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
