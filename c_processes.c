#include "demo_programs.h"
#include "pcb.h"
#include "init_processes.h"
#include "interupt_shims.h"
#include "sorts.h"

int init_c_processes(void)
{
	addNewProcess(hello_world);
	addNewProcess(hello_mars);
	
	return 0;
}
