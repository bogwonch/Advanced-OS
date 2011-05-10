#include "scheduling.h"
#include "tables.h"
#include "interupt_shims.h"
#include <assert.h>
#include <stdio.h>

extern void schedule_process(PCB *proc);
extern void save_yielded(PCB *proc, void *link);

void kill_process(void)
{
	int pid = os_state.current_pid;
	printf("\nINFO: Killing process PID:%d\n", pid);
	mark_dead(pid);
}

void yield_process(void *link)
{
	int pid = os_state.current_pid;
	printf("\nINFO: Yielding from process PID:%d\n", pid);
	mark_ready(pid);
	save_yielded(&pcb_table[pid], link);
}

void run_process(int pid)
{
	if (pcb_table[pid].state != READY)
		;
		
}

void mark_dead(int pid)
{
	pcb_table[pid].state = DEAD;
}

void mark_ready(int pid)
{
	pcb_table[pid].state = READY;
}

PCB *scheduleNextRR(void)
{
	printf("\nWARN: This isn't acutally used.\n"
		 "WARN: call round_robin_schedule to get the id of the next PID\n");
	
	return &(pcb_table[round_robin_schedule()]);
}

/* The actual round robin algorithm */
int round_robin_schedule(void)
{
	int ppid = os_state.current_pid;
	int pid = ppid;
	
	do 
	{
		pid += 1;
		pid %= PCB_TABLE_SIZE;
		
		if (pcb_table[pid].state == READY)
		{
			
			return pid;
		}
	}
	while (pid != ppid);
	
	// We have no more processes to schedule... 
	return NO_PID_READY;;
}

void schedule_next(void)
{
	//int pid = round_robin_schedule();
	int pid = lottery_scheduler();
	
	if (pid <= NO_PID_READY)
	{
		printf("\nWARN: No process is ready to run\n");
		Shutdown();
	}
	printf("\nINFO: Scheduling PID:%d\n", pid);
	os_state.current_pid = pid;
	schedule_process(pcb_table+pid);
}


