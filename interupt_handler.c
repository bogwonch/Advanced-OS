#include "interupt_handler.h"
#include "scheduling.h"
#include "interupt_shims.h"
#include "ioroutines.h"
#include <stdio.h>

extern int add_process(int (*)(void));
extern void shutdown_system(void);

int interupt_handler(int interupt, void *arg)
{
	switch(interupt)
	{
	default:
		printf("ERROR: Illegal interupt %d\n", interupt);
	case 0xD13:
		printf("INFO: System is shutting down\n");
		addNewProcess((int (*)(void))shutdown_system);
	
	case 0:
		kill_process();
	case 42:
		schedule_next();
		break;
		
	case 1:
		print_hex((unsigned int)arg);
		break;
	
	case 2:
		print_dec((int)arg);
		break;
	
	case 3:
		print_char((unsigned int)arg);
		break;
	
	case 4:
		print_string((unsigned char *)arg);
		break;
		
	case 5:
	case 10:
		add_process((int (*)(void))arg);
		break;
		
	case 11:
		yield_process((void *)arg);
		schedule_next();
		
		break;
	
	}
	
	
	return 0;
}

