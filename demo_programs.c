#include "demo_programs.h"
#include "interupt_shims.h"
#include <stdio.h>


int hello_world(void)
{
	printf("Hello World\n");
	addNewProcess(bye_world);
	Yield();
	printf("Ooh we're back home!\n");
	return 0;
}

int hello_mars(void)
{
	printf("Hello Mars\n");
	addNewProcess(bye_mars);
	return 0;
}

int hello_galaxy(void)
{
	printf("Hello Galaxy\n");
	addNewProcess(bye_galaxy);
	return 0;
}

int bye_world(void)
{
	printf("Goodbye, fair World\n");
	return 0;
}

int bye_mars(void)
{
	printf("Goodbye, fair Mars\n");
	return 0;
}

int bye_galaxy(void)
{
	printf("Goodbye, fair Galaxy\n");
	return 0;
}


