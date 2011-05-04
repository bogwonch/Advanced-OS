#include <stdio.h>
#include "pcb.h"
#include "init_processes.h"
#include "interupt_shims.h"
#include "scheduling.h"
#include "tables.h"

extern PCB pcb_table[PCB_TABLE_SIZE];

int main(void)
{
	printf("INFO: Initialised stacks dropped to C\n");
	init_pcb_table();
	printf("INFO: Initialised process table\n");
	init_asm_processes();
	printf("INFO: Loaded asm processes\n");
	init_c_processes();
	printf("INFO: Loaded C processes\n");
	printf("INFO: Starting scheduling\n");
	
	Kill();
	// UNREACHABLE CODE 
	Shutdown();
	return 0;
}

