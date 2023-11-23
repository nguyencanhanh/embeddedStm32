#include <rtos.h>

uint8_t numberTask = 0;
uint8_t maxTask;
uint8_t curent_task = 1;
TCB_t user_task[MAX_TASK];
GTIME gTime[MAX_TASK];

// QUEUE

Queue* vQueueCreate(uint8_t size) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));

    if (queue != NULL) {
        queue->front = 0;
        queue->rear = 0;
        queue->count = 0;
        queue->size = size;
    }
    return queue;
}

void vQueueDelete(Queue *queue) {
    if (queue != NULL) {
        free(queue);
    }
}

void vQueueSendToFront(Queue *queue, void *data, uint8_t dataSize) {
    if (queue->count < queue->size) {
        QueueItem item;
        item.data = malloc(dataSize);
        memcpy(item.data, data, dataSize);
        item.dataSize = dataSize;

        queue->front = (queue->front - 1 + queue->size) % queue->size;
        queue->items[queue->front] = item;
        queue->count++;
    }
}

void vQueueSend(Queue *queue, void *data, uint8_t dataSize) {
	if (queue->count < queue->size) {
		QueueItem item;
		item.data = malloc(dataSize);
		memcpy(item.data, data, dataSize);
		item.dataSize = dataSize;
		queue->items[queue->rear] = item;
		queue->rear = (queue->rear + 1) % queue->size;
		queue->count++;
	}
}

void vQueueReceive(Queue *queue, void *outputData) {
    if (queue->count > 0) {
        QueueItem item = queue->items[queue->front];
        memcpy(outputData, item.data, item.dataSize);

        free(item.data);

        queue->front = (queue->front + 1) % queue->size;
        queue->count--;
    }
}

void createTask(void (*myTask)(void)){
  user_task[numberTask+1].task_handler = myTask;
  numberTask++;
  maxTask = numberTask+1;
}

void init_systick_timer(uint32_t tick_hz){
	SysTick->LOAD |= ((SYSTICK_TIM_CLK / TICK_HZ) - 1) & 0x00FFFFFF;
	SysTick->CTRL |= (7 << 0);
}

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack){
	__asm volatile ("MSR MSP, %0": : "r"(sched_top_of_stack));
	__asm volatile ("BX LR");
}

void init_task_stack(void(*idleTask)(void)){
	user_task[0].psp_value = (SRAM_END - (numberTask * SIZE_TASK_STACK));
	user_task[0].task_handler = idleTask;

	uint32_t *pPSP;
	for(int i = 0; i < maxTask; i++){
		user_task[i].curent_state = TASK_RUNNING_STATE;
		gTime[i].suspenTask = RESUME_TASK;
		if(i < numberTask){
			user_task[i+1].psp_value = (SRAM_END - (i * SIZE_TASK_STACK));
		}
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

uint32_t get_psp_value(void){
	return user_task[curent_task].psp_value;
}

void save_psp_value(uint32_t curent_psp_value){
	user_task[curent_task].psp_value = curent_psp_value;
}

void update_next_task(void){
	int state = TASK_BLOCK_STATE;
	for (int i = 0; i < maxTask; i++){
		curent_task ++;
		curent_task %= maxTask;
		state = user_task[curent_task].curent_state;
		if((state == TASK_RUNNING_STATE) && (curent_task != 0))
			break;
	}
	if (state != TASK_RUNNING_STATE)
		curent_task = 0;
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
	gTime[curent_task].g_tick_count = 0;
	gTime[curent_task].stateDelay = IN_DELAY;
	if(curent_task){
		user_task[curent_task].block_count = tick_count;
		user_task[curent_task].curent_state = TASK_BLOCK_STATE;
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	}
	ENABLE_IRQ();
}

void unblock_task(void){
	for (int i = 1; i < maxTask; i++){
		if (user_task[i].curent_state != TASK_RUNNING_STATE){
			if((user_task[i].block_count <= gTime[i].g_tick_count) && (gTime[i].suspenTask != SUSPEN_TASK)){
				user_task[i].curent_state = TASK_RUNNING_STATE;
				gTime[i].stateDelay = OUT_DELAY;
			}
		}
	}
}

void rtosInit(void (*idleTask)(void)){
	enable_rpocessor_faults();
	init_scheduler_stack((SRAM_END - ((numberTask+1) * SIZE_TASK_STACK)));
	init_task_stack(idleTask);
	init_systick_timer(TICK_HZ);
	swich_sp_to_psp();
	user_task[1].task_handler();
}


void suspenTask(void (*task)(void)){
	for (int i = 1; i < numberTask + 1; i++){
		if (user_task[i].task_handler == task){
			user_task[i].curent_state = TASK_BLOCK_STATE;
			gTime[i].suspenTask = SUSPEN_TASK;
			break;
		}
	}
}

void resumeTask(void (*task)(void)){
	for (int i = 1; i < numberTask + 1; i++){
		if (user_task[i].task_handler == task){
			user_task[i].curent_state = TASK_RUNNING_STATE;
			gTime[i].suspenTask = RESUME_TASK;
			break;
		}
	}
}
//
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
//
void SysTick_Handler(){
	for (int i = 1; i < maxTask; i++){
		if(gTime[i].stateDelay != OUT_DELAY)
			gTime[i].g_tick_count++;
	}
	unblock_task();
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

