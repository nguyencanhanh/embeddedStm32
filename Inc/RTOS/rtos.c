//#include <rtos.h>
//
//extern uint8_t curent_task;
//TCB_t user_task[MAX_TASK];
//
//void init_systick_timer(uint32_t tick_hz){
//	SysTick->LOAD |= ((SYSTICK_TIM_CLK / TICK_HZ) - 1) & 0x00FFFFFF;
//	SysTick->CTRL |= (7 << 0);
//}
//
//__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack){
//	__asm volatile ("MSR MSP, %0": : "r"(sched_top_of_stack));
//	__asm volatile ("BX LR");
//}
//
//void init_task_stack(void (*MainFunction)()){
//	user_task[0].psp_value = IDLE_STACK_START;
//	user_task[1].psp_value = T1_STACK_START;
//	user_task[2].psp_value = T2_STACK_START;
//	user_task[3].psp_value = T3_STACK_START;
//	user_task[4].psp_value = T4_STACK_START;
//
//	user_task[0].task_handler = idle_task;
//	user_task[1].task_handler = MainFunction;
//	user_task[2].task_handler = task2_handler;
//	user_task[3].task_handler = task3_handler;
//	user_task[4].task_handler = task4_handler;
//
//	uint32_t *pPSP;
//	for(int i = 0; i < MAX_TASK; i++){
//		user_task[i].task_handler = MainFunction;
//		user_task[i].curent_state = TASK_RUNNING_STATE;
//		pPSP = (uint32_t*) user_task[i].psp_value;
//		pPSP--;
//		*pPSP = DUMMY_XPSR;
//		pPSP--;
//		*pPSP = (uint32_t) user_task[i].task_handler;
//		pPSP--;
//		*pPSP |= 0xFFFFFFFD;
//		for (int j = 0; j<13; j++){
//			pPSP--;
//			*pPSP = 0;
//
//		}
//		user_task[i].psp_value = (uint32_t)pPSP;
//	}
//}
//
//void enable_rpocessor_faults(void){
//	SCB->SHCSR |= (7 << 16);
//}
//
//uint32_t get_psp_value(void){
//	return user_task[curent_task].psp_value;
//}
//
//void save_psp_value(uint32_t curent_psp_value){
//	user_task[curent_task].psp_value = curent_psp_value;
//}
//
//void update_next_task(void){
//	int state = TASK_BLOCK_STATE;
//	for (int i =0; i < MAX_TASK; i++){
//		curent_task ++;
//		curent_task %= MAX_TASK;
//		state = user_task[curent_task].curent_state;
//		if((state == TASK_RUNNING_STATE) && (curent_task != 0)){
//			break;
//		}
//	}
//	if (state != TASK_RUNNING_STATE){
//		curent_task = 0;
//	}
//}
//
//__attribute__((naked)) void swich_sp_to_psp(void){
//	__asm volatile ("PUSH {LR}");
//	__asm volatile ("BL get_psp_value");
//	__asm volatile ("MSR PSP, R0");
//	__asm volatile ("POP {LR}");
//
//	__asm volatile ("MOV R0, #0x02");
//	__asm volatile ("MSR CONTROL, R0");
//	__asm volatile ("BX LR");
//
//}
//
//
//void task_delay(uint32_t tick_count){
//	DISABLE_IRQ();
//	extern uint32_t g_tick_count;
//	g_tick_count = 0;
//	if(curent_task){
//		user_task[curent_task].block_count = tick_count;
//		user_task[curent_task].curent_state = TASK_BLOCK_STATE;
//		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
//	}
//	ENABLE_IRQ();
//}
//
//void unblock_task(void){
//	for (int i = 1; i < MAX_TASK; i++){
//		if (user_task[i].curent_state != TASK_RUNNING_STATE){
//			if(user_task[i].block_count == g_tick_count){
//				user_task[i].curent_state = TASK_RUNNING_STATE;
//			}
//		}
//	}
//}
