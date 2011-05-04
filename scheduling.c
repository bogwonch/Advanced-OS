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
	printf("INFO: Killing process PID:%d\n", pid);
	mark_dead(pid);
}

void yield_process(void *link)
{
	int pid = os_state.current_pid;
	printf("INFO: Yielding from process PID:%d\n", pid);
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
			printf("INFO: Scheduling PID:%d\n", pid);
			return pid;
		}
	}
	while (pid != ppid);
	
	// We have no more processes to schedule... SHUTDOWN
	printf("WARN: No process is ready to run\n");
	Shutdown();
	
	
	// UNREACHABLE CODE
	assert(0);
	return -1;
}

void schedule_next(void)
{
	int pid = round_robin_schedule();
	
	os_state.current_pid = pid;
	schedule_process(pcb_table+pid);
}


