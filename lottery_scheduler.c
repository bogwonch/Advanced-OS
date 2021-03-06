#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tables.h"
#include "scheduling.h"
#include "pcb.h"


#define TICKETS 100

int lottery_scheduler(void)
{
	int tickets[TICKETS];
	int pids[PCB_TABLE_SIZE];
	
	int i = 0;
	int j = 0;
	int k;
	int total = 0;
	
	// Find how many processes we can schedule
	for (; i < PCB_TABLE_SIZE; i++)
	{
		if (pcb_table[i].state == READY)
		{
			total += pcb_table[i].priority;
			pids[j++] = pcb_table[i].pid;
			pids[j] = 0;
		}
	}
	
	printf("\nINFO: %d processes ready to be run\n", j);
	
	// If nothing ready
	if (total == 0)
		return NO_PID_READY;
	
	// Assign tickets
	i = 0;
	while (j)
	{
		j -= 1;
		k = pcb_table[pids[j]].priority;
		k *= TICKETS / total;
		
		printf("\nINFO: Assigning %d tickets to process %d\n", k, pids[j]);
		
		while (k--)
		{
			tickets[i++] = pids[j];
		}
	}
		
	// Pick a ticket
	//srand(clock());
	return tickets[rand()%(i-1)];
	
}
