#ifndef PCB_H
#define PCB_H

#define N_REGS 16
#define PCB_TABLE_SIZE 64
#define PROCESS_STACK_SIZE 0x4000

/* Some special registers */
#define SP 13
#define LR 14
#define PC 15

#define READY 0
#define RUNNING 1
#define BLOCKED 2
#define DEAD 3

/* A PCB */
typedef struct pcb_t
{
	int pid;
	int state;
	int reg[N_REGS];
	int spsr;
	int stack[PROCESS_STACK_SIZE];

}
PCB;

extern void create_pcb(PCB *, int, int(*)(void));
extern int add_process(int (*)(void));
extern void init_pcb_table(void);
extern int find_free_pid(PCB *table);

#endif
