#include <stdio.h>
#include "pcb.h"
#include "init_processes.h"
#include "interupt_shims.h"
#include "scheduling.h"
#include "tables.h"

extern PCB pcb_table[PCB_TABLE_SIZE];

int main(void)
{
	//printf("INFO: Initialised stacks dropped to C\n");
	//init_pcb_table();
	//printf("INFO: Initialised process table\n");
	printf("\nINFO: Welcome to AdvancedOS.\n");
	printf(  "INFO: Main has been scheduled for your convenience\n");
	printf(  "INFO: Adding Assembler process loading to the schedule\n");
	addNewProcess((int (*)(void))init_asm_processes);
	printf(  "INFO: Main is yielding to allow something else to run for a bit\n");
	
	//Yield();
	
	printf("\nINFO: Adding C Process loading to the schedule\n");
	addNewProcess((int (*)(void))init_c_processes);
	printf(  "INFO: System initialisation complete\n");
	
	
	Kill();
	// UNREACHABLE CODE 
	Shutdown();
	return 0;
}

