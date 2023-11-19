
#ifndef RTOS_RTOS_H_
#define RTOS_RTOS_H_

#include <stm32f1xx.h>

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
#define T5_STACK_START            (SRAM_END - (4 * SIZE_TASK_STACK))
#define T6_STACK_START            (SRAM_END - (5 * SIZE_TASK_STACK))
#define T7_STACK_START            (SRAM_END - (6 * SIZE_TASK_STACK))
#define IDLE_STACK_START          (SRAM_END - (7 * SIZE_TASK_STACK))
#define SCHED_STACK_START         (SRAM_END - (8 * SIZE_TASK_STACK))

#define TICK_HZ                   1000U
#define HSI_CLOCK                 8000000U
#define SYSTICK_TIM_CLK           HSI_CLOCK

#define MAX_TASK                  8

#define DISABLE_IRQ()             do{__asm volatile("MOV R0, #0x1"); __asm volatile("MSR PRIMASK,R0");} while(0)
#define ENABLE_IRQ()              do{__asm volatile("MOV R0, #0x0"); __asm volatile("MSR PRIMASK,R0");} while(0)

typedef struct{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t curent_state;
	void(*task_handler)(void);
}TCB_t;

void idle_task(void);

void init_systick_timer(uint32_t tick_hz);

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);

void init_task_stack(void (*MainFunction)());

__attribute__((naked)) void swich_sp_to_psp(void);

void enable_rpocessor_faults(void);

void save_psp_value(uint32_t curent_psp_value);

uint32_t get_psp_value(void);

void update_next_task(void);

void unblock_task(void);

void task_delay(uint32_t tick_count);


#endif /* RTOS_RTOS_H_ */
