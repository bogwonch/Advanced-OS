#ifndef INTERUPT_SHIMS_H_
#define INTERUPT_SHIMS_H_

extern int addNewProcess(int (*)(void));
extern void Kill(void);
extern void Shutdown(void);
extern void Yield(void);

#endif /*INTERUPT_SHIMS_H_*/
