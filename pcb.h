#ifndef PCB_H
#define PCB_H

#define N_REGS 16
#define PCB_TABLE_SIZE 64
#define PROCESS_STACK_SIZE 0x4000

/* Some special registers */
#define SP 13
#define LR 14
#define PC 15

#define READY 1
#define RUNNING 2
#define BLOCKED 3
#define DEAD 0

/* A PCB */
typedef struct pcb_t
{
	int pid;
	int state;
	int reg[N_REGS];
	int spsr;
	int stack[PROCESS_STACK_SIZE];
	int priority;

}
PCB;

extern void create_pcb(PCB *, int, int(*)(void));
extern int add_process(int (*)(void));
extern void init_pcb_table(void);
extern int find_free_pid(PCB *table);

#endif
