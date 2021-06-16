#include "bsp_system.h"


/* 加入以下代码,支持printf函数,而不需要选择use MicroLIB	*/
#pragma import(__use_no_semihosting)             
/* 标准库需要的支持函数 */                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       

/*定义_sys_exit()以避免使用半主机模式  */  
_sys_exit(int x) 
{ 
	x = x; 
} 


// THUMB指令不支持汇编内联

/* 执行WFI指令 */
void WFI_SET(void){
	
	__ASM volatile("wfi");		  
}

/* 关闭所有中断 */
void INTX_DISABLE(void){
	
	__ASM volatile("cpsid i");
}

/* 开启所有中断 */
void INTX_ENABLE(void){
	
	__ASM volatile("cpsie i");		  
}

/* 设置堆栈地址 */
//addr:栈顶地址
__asm void MSR_MSP(uint32_t addr){
	
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
