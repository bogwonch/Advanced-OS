#ifndef SCHEDULING_H_
#define SCHEDULING_H_

void kill_process(void);
void run_process(int);
void yield_process(void *);
void schedule_next(void);
void mark_dead(int);
void mark_ready(int);

#endif /*SCHEDULING_H_*/
