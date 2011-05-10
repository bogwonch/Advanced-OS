#ifndef SCHEDULING_H_
#define SCHEDULING_H_
#include "pcb.h"

void kill_process(void);
void run_process(int);
void yield_process(void *);
void schedule_next(void);
void mark_dead(int);
void mark_ready(int);

int lottery_scheduler(void);
int round_robin_schedule(void);

PCB *scheduleNextRR(void);

#define NO_PID_READY (-1)

#endif /*SCHEDULING_H_*/
