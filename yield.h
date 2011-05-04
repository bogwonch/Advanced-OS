#ifndef YIELD_H_
#define YIELD_H_
#include "pcb.h"

typedef struct {
	int reg[N_REGS];
	int spsr;
} Yielding;

#endif /*YIELD_H_*/
