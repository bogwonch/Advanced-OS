#include "demo_programs.h"
#include "pcb.h"
#include "init_processes.h"
#include "interupt_shims.h"
#include "sorts.h"

int dummy(void);
extern int main(void);

int dummy(void)
{
	return 0;
}

int init_c_processes(void)
{
	addNewProcess(sort_main);
	//addNewProcess(dummy);
	//addNewProcess(hello_world);
	//addNewProcess(main);
	
	return 0;
}


