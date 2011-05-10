#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include "interupt_shims.h"
#include "tables.h"

#define INITIAL_SPSR 0x10

/*  Just for reference!
typedef struct pcb_t
{
	int pid;
	enum { READY, RUNNING, BLOCKED, DEAD } state;
	int register[16];
	int spsr;
}
PCB;
*/

void create_pcb(PCB *new, int pid, int(*proc)(void))
{
	//int i;
	new->pid = pid;
	new->state = READY;
	/*
	// No initialization for speed
	for (i = 0; i < N_REGS; i++)
		new->reg[i] = 0;
	*/
	new->reg[PC] = (int)proc;
	new->spsr = INITIAL_SPSR;
	new->reg[LR] = (int)Kill;
	new->reg[SP] = (int)&(new->stack[PROCESS_STACK_SIZE-1]); // Descending stack so use the END
	new->priority = 1+ (rand() % 5);
}

int add_process(int (*proc)(void))
{
	int pid = find_free_pid(pcb_table);
	
	if (pid >= 0)
	{
		printf("\nINFO: Creating process with PID %d\n", pid);
		create_pcb(&pcb_table[pid], pid, proc);
		return 0;
	}
	
	printf("\nWARN: Couldn't create process for process at 0x%X\n", (int)proc);
	return -1;
}

// Replaced with assembly in start.s
void init_pcb_table(void)
{
	int i;
	for (i = 0; i < PCB_TABLE_SIZE; i++)
		pcb_table[i].state = DEAD;
	
	os_state.current_pid = PCB_TABLE_SIZE-1;
}

int find_free_pid(PCB *table)
{
	int i;
	for (i = 0; i < PCB_TABLE_SIZE; i++)
		/* Yes os_state thing is stupid.  Blame the arm scatterloader for being stupid */
		if (table[i].state == DEAD && i != os_state.current_pid)
			return i;
	
	printf("\nWARN: No space for creating any more processes.\n");
	
	return -1;
}

