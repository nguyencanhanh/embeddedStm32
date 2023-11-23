
#ifndef RTOS_RTOS_H_
#define RTOS_RTOS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stm32f1xx.h>

#define QUEUE_SIZE 				  10

#define DUMMY_XPSR                0x01000000

#define TASK_RUNNING_STATE        0
#define TASK_BLOCK_STATE          1

#define OUT_DELAY     			  0
#define IN_DELAY	       		  1

#define SUSPEN_TASK     		  0
#define RESUME_TASK          	  1

#define SIZE_TASK_STACK           512
#define SIZE_SCHED_STACK          512

#define SRAM_START                0x20000000U
#define SIZE_SRAM                 (20 * 1024)
#define SRAM_END                  (SRAM_START + SIZE_SRAM)

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

typedef struct{
	uint32_t g_tick_count;
	uint8_t stateDelay;
	uint8_t suspenTask;
}GTIME;

typedef struct {
    void *data;
    uint8_t dataSize;
} QueueItem;

typedef struct {
    QueueItem items[QUEUE_SIZE];
    uint8_t front;
    uint8_t rear;
    uint8_t count;
    uint8_t size;
} Queue;

extern uint8_t curent_task;
extern uint8_t numberTask;
extern uint8_t maxTask;
extern uint8_t queue[];
extern GTIME gTime[MAX_TASK];
extern TCB_t user_task[MAX_TASK];

void createTask(void (*myTask)(void));

/*Init rtos*/
void rtosInit(void (*idleTask)(void));
void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_task_stack(void (*idleTask)(void));
/*End init rtos*/

/*Queue API*/
Queue* vQueueCreate(uint8_t size);
void vQueueDelete(Queue *queue);
void vQueueSend(Queue *queue, void *data, uint8_t dataSize);
void vQueueSendToFront(Queue *queue, void *data, uint8_t dataSize);
void vQueueReceive(Queue *queue, void *outputData);
/*End queue API*/

__attribute__((naked)) void swich_sp_to_psp(void);

void enable_rpocessor_faults(void);

void save_psp_value(uint32_t curent_psp_value);

uint32_t get_psp_value(void);

void update_next_task(void);

void unblock_task(void);

void suspenTask(void (*task)(void));

void resumeTask(void (*task)(void));

void task_delay(uint32_t tick_count);


#endif /* RTOS_RTOS_H_ */
