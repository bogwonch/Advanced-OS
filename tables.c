#include "pcb.h"
#include "tables.h"
#include "state.h"
#include "yield.h"

PCB pcb_table[PCB_TABLE_SIZE];
OS_State os_state;
Yielding yield;
