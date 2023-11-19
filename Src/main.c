#include <stdio.h>
#include <stdint.h>
#include "stm32f103.h"
#include "GPIO_Configure.h"
#include "TIM_Configure.h"
#include "UART_Configure.h"
#include "DMA_Configure.h"
#include "ADC_Configure.h"
#include "I2C_Configure.h"
#include "LiquidCrystal_I2C.h"
//#include "rtos.h"

int __io_putchar(int ch) {
    UART_SendData((char*)&ch);
    return ch;
}

#define LED12_ON				  GPIOB->BSRR |= (1 << 12)
#define LED12_OFF 	  			  GPIOB->BSRR |= (1 << 28)
#define LED12_TOGGLE 			  GPIOB->ODR  ^= (1 << 12)

#define DUMMY_XPSR                0x01000000

#define TASK_RUNNING_STATE        0
#define TASK_BLOCK_STATE          1

#define SIZE_TASK_STACK           512
#define SIZE_SCHED_STACK          512

#define SRAM_START                0x20000000U
#define SIZE_SRAM                 (20 * 1024)
#define SRAM_END                  (SRAM_START + SIZE_SRAM)

#define T1_STACK_START            SRAM_END
#define T2_STACK_START            (SRAM_END - (1 * SIZE_TASK_STACK))
#define T3_STACK_START            (SRAM_END - (2 * SIZE_TASK_STACK))
#define T4_STACK_START            (SRAM_END - (3 * SIZE_TASK_STACK))
#define IDLE_STACK_START          (SRAM_END - (4 * SIZE_TASK_STACK))
#define SCHED_STACK_START         (SRAM_END - (5 * SIZE_TASK_STACK))

#define TICK_HZ                   1000U
#define HSI_CLOCK                 8000000U
#define SYSTICK_TIM_CLK           HSI_CLOCK

#define MAX_TASK                  5

#define DISABLE_IRQ()             do{__asm volatile("MOV R0, #0x1"); __asm volatile("MSR PRIMASK,R0");} while(0)
#define ENABLE_IRQ()              do{__asm volatile("MOV R0, #0x0"); __asm volatile("MSR PRIMASK,R0");} while(0)

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void idle_task(void);
void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_task_stack(void);
__attribute__((naked)) void swich_sp_to_psp(void);
void enable_rpocessor_faults(void);

void save_psp_value(uint32_t curent_psp_value);
uint32_t get_psp_value(void);
void update_next_task(void);
void task_delay(uint32_t tick_count);


typedef struct{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t curent_state;
	void(*task_handler)(void);
}TCB_t;

TCB_t user_task[MAX_TASK];

uint8_t GPIOB_Pin[] = {12,13};
uint8_t GPIOB_mode[] = {1,1};

uint32_t g_tick_count = 0;
uint8_t curent_task = 1;

int main(void)
{
	GPIO_configureRCC("B");
	GPIO_configure((GPIO_TypeDef*)GPIOB, (uint8_t*)GPIOB_Pin ,(uint8_t*)GPIOB_mode);
	enable_rpocessor_faults();
	init_scheduler_stack(SCHED_STACK_START);

	init_task_stack();
	init_systick_timer(TICK_HZ);
	swich_sp_to_psp();
	task1_handler();

	 while (1)
	  {

	  }
}

void idle_task(void){
	while(1);
}

void task1_handler(void){
	while(1){
		printf("oke");
	}
}
void task2_handler(void){
	while(1){
		printf("oke");
	}
}
void task3_handler(void){
	while(1){
		LED12_TOGGLE;
		task_delay(1000);
		printf("oke");
	}
}
void task4_handler(void){
	while(1){
		printf("oke");
	}
}

void init_systick_timer(uint32_t tick_hz){
	SysTick->LOAD |= ((SYSTICK_TIM_CLK / TICK_HZ) - 1) & 0x00FFFFFF;
	SysTick->CTRL |= (7 << 0);
}

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack){
	__asm volatile ("MSR MSP, %0": : "r"(sched_top_of_stack));
	__asm volatile ("BX LR");
}

void init_task_stack(void){

	user_task[0].curent_state = TASK_RUNNING_STATE;
	user_task[1].curent_state = TASK_RUNNING_STATE;
	user_task[2].curent_state = TASK_RUNNING_STATE;
	user_task[3].curent_state = TASK_RUNNING_STATE;
	user_task[4].curent_state = TASK_RUNNING_STATE;

	user_task[0].psp_value = IDLE_STACK_START;
	user_task[1].psp_value = T1_STACK_START;
	user_task[2].psp_value = T2_STACK_START;
	user_task[3].psp_value = T3_STACK_START;
	user_task[4].psp_value = T4_STACK_START;

	user_task[0].task_handler = idle_task;
	user_task[1].task_handler = task1_handler;
	user_task[2].task_handler = task2_handler;
	user_task[3].task_handler = task3_handler;
	user_task[4].task_handler = task4_handler;

	uint32_t *pPSP;
	for(int i = 0; i < MAX_TASK; i++){
		pPSP = (uint32_t*) user_task[i].psp_value;
		pPSP--;
		*pPSP = DUMMY_XPSR;
		pPSP--;
		*pPSP = (uint32_t) user_task[i].task_handler;
		pPSP--;
		*pPSP |= 0xFFFFFFFD;
		for (int j = 0; j<13; j++){
			pPSP--;
			*pPSP = 0;

		}
		user_task[i].psp_value = (uint32_t)pPSP;
	}
}

void enable_rpocessor_faults(void){
	SCB->SHCSR |= (7 << 16);
}

void HardFault_Handler(void){
	printf("HardFault_Handler\n");
	while(1);
}

void MemManage_Handler(){
	printf("MemManage_Handler\n");
	while(1);
}

void BusFault_Handler(){
	printf("BusFault_Handler\n");
	while(1);
}

uint32_t get_psp_value(void){
	return user_task[curent_task].psp_value;
}

void save_psp_value(uint32_t curent_psp_value){
	user_task[curent_task].psp_value = curent_psp_value;
}

void update_next_task(void){
	int state = TASK_BLOCK_STATE;
	for (int i =0; i < MAX_TASK; i++){
		curent_task ++;
		curent_task %= MAX_TASK;
		state = user_task[curent_task].curent_state;
		if((state == TASK_RUNNING_STATE) && (curent_task != 0)){
			break;
		}
	}
	if (state != TASK_RUNNING_STATE){
		curent_task = 0;
	}
}

__attribute__((naked)) void swich_sp_to_psp(void){
	__asm volatile ("PUSH {LR}");
	__asm volatile ("BL get_psp_value");
	__asm volatile ("MSR PSP, R0");
	__asm volatile ("POP {LR}");

	__asm volatile ("MOV R0, #0x02");
	__asm volatile ("MSR CONTROL, R0");
	__asm volatile ("BX LR");

}


void task_delay(uint32_t tick_count){
	DISABLE_IRQ();
	g_tick_count = 0;
	if(curent_task){
		user_task[curent_task].block_count = tick_count;
		user_task[curent_task].curent_state = TASK_BLOCK_STATE;
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	}
	ENABLE_IRQ();
}

__attribute__((naked)) void PendSV_Handler(void){
    // Save the current task's context
    __asm volatile ("MRS R0, PSP");
    __asm volatile ("STMDB R0!, {R4-R11}");
    __asm volatile ("PUSH {LR}");
    __asm volatile ("BL save_psp_value");
    __asm volatile ("BL update_next_task");

    // Load the next task's context
    __asm volatile ("BL get_psp_value");
    __asm volatile ("LDMIA R0!, {R4-R11}");
    __asm volatile ("MSR PSP, R0");

    __asm volatile ("POP {LR}");
    __asm volatile ("BX LR");
}

void unblock_task(void){
	for (int i = 1; i < MAX_TASK; i++){
		if (user_task[i].curent_state != TASK_RUNNING_STATE){
			if(user_task[i].block_count == g_tick_count){
				user_task[i].curent_state = TASK_RUNNING_STATE;
			}
		}
	}
}

void SysTick_Handler(){
	g_tick_count++;
	unblock_task();
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

