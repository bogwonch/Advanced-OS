# Embedded Systems Integration

## Summary

I have implemented:
 * Task 1---an OS that uses PCBs for context storage and is capable of multi-tasking
 * Task 2---a round robin scheduling algorithm
 * Task 3---a yielding mechanism to allow processes to be suspended
 * Verified sorts.c and HelloOS work as predicted

I have also implemented
 * An advanced scheduling algorithm---lottery scheduling
 * the OS as a first class citizen

I might have implemented
 * Dynamic data structures---the PCB table is of a fixed size but there is an allocator using the first free algorithm to dynamically find room in it.


## Task one

The advanced OS starts slightly differently to most (that I've seen) as I have implemented almost everything as a process.  The operating system starts in starts.s, and sets up the system stack.  It then initialises the PCB table slots to indicate they are all free.

With the PCB table empty it adds a new process: the C main function.  It then calls the scheduler to run it.  Since this is the only process currently it will always be run.

Importantly I do not set up a single user-mode stack here or drop from SVC mode.  All processes are created with their own stacks, and are set to run in user mode.  There is no need to drop priviledges or set up a stack as this will occur when the processes are scheduled.  The downside to this aproach is that since we have yet to call the C initialisation code we don't have access to printf, so no debugging information is yet available.  The upside is that we can re-add main to the schedule to reschedule the operating system.

Processes are created by giving them a PCB in the table.  Each PCB is initially set up with its own stack, set of registers, and state (always user-mode).  The PC is set to the start of the function implementing the process, the SP set to the end of the process's stack, and the LR is set to a function that calls the kill-process interrupt.  The advantage of this approach (over explicitly calling kill) is that *any* function can be run as a process without changing its syntax (providing it doesn't overwrite the LR).  The exception here is that main does require an explicit kill as the ARM compiler adds code to shutdown the emulator on its return.

Each process is given a 4KB stack.  This is overkill for most applications however the ARM compiler occasionally likes to muck about with the SP (for reasons I don't understand, it doesn't touch the memory it skips over as far as I can tell).  It seems to do this randomly on some C functions even between compiles, but it usually places one before the sorts.c main.  At the end of the function it returns the SP to the usual place.  4KB seems big enough to avoid this ever being an issue.  Processes are always added using a software interrupt, this allows the processes adding them to run as user processes.

The PCB also contains a priority field.  The priority is assigned randomly between 1 and 5 for demonstation.

Processes are scheduled by copying the PCB into the processor's registers. This causes SVC mode to be dropped, and the stack set up.

When main runs it does three things: it adds a process to add the assembly processes, yields (to demonstrate it can), and adds a process to add the C processes.


## Task two

A round-robin scheduling algorithm is implemented.  Working from the last running PID it searches the PCB table for another ready process to run.  If it gets back to the last PID and that process is also not ready to run it returns NO-PID-READY which triggers a shutdown.


## Task three

All processes can be yielded by calling software-interrupt #11 (or Yield()).  This causes the current registers to be copied from the processor into the appropriate PCB (dropping to System mode where appropriate).  The exact code can be seen in schedule.s.  After the registers are copied the PCB is set to READY so it can be run again.  Registers 0-3 are not stored.

[insert picture]


## Advanced Scheduling

I also implemented a lottery scheduler as well as the round robin.  A lottery scheduler works by assigning lottery tickets to all ready processes.  Higher priority processes are given more tickets.  The scheduler picks a ticket at random and the process that owns it is scheduled next.

This sort of scheduler has several advantages over a round-robin: it guarantees no process will be starved of running time since all processes have a chance of being run at every scheduling (though higher priority ones are more likely to be).  

As implemented the scheduler is cooporative however it is relatively easy to make a preemptive one by copying however many instructions you wish to run to a buffer then updating the PCBs PC accordingly and adding a Yield call at the end. The processors PC can be set to the start of the buffer, and the registers updated as normal.

Code for the lottery scheduler can be found in lottery-scheduler.c.


## First class operating system

All loading code, and system initialisation is run as seperate process.  All code which must be allowed to run to completions (things altering the PCB table) is kept within SVC mode, and anything else (shutdown for example) is treated as a user process.  

This means that main() can yield at any time, and the basic processing (including shutdown) can be made to yield if you require it.

To demonstrate this the main and shutdown both have a yield call in them.


## Dynamic data structures

Whilst the PCB table is of a fixed size, PCB blocks can be reused and reallocated.  An allocation routine (find-free-pcb in pcb.c) behaves uses a first fit algorithm to dynamically reallocate dead PCBs and behaves similarly to UNIX v6's malloc function (see line 2528 of the Lion's Commentary).  

Having a fixed range in memory where the PCB table can expand into is analogous to the heap in a modern operating system, and so I believe this makes it as dynamic as any linked list implementation.  Arguments that there is still a maximum number of simultaneous processes I believe to be irrelevant as there will always be a maximum number of processes as it is limited by memory available.  If someone were to port my OS to another system they could change the limit appropriately, just as they would set the heap size.

I did not use the malloc functions provided in stdlib.h as I do not see how the processor could  judge what parts of my memory were in use or were free at runtime without me implementing memory protection.  Since in most operating systems malloc places information about memory usage in a segmentation table, and I don't have one I honestly am not sure what it's doing.  I suspect it's using the simulator to guess (or there is a hidden heap somewhere set up for me by the C main function).


## Appendix A

A trace of the output showing randomised scheduling and yielding.  Yields have been added to the sorts routine between each of the sorting routines, as well as the main process and shutdown processes.  HelloOS is loaded in asm-processes, and the sorts main is loaded as a C process. 

<code>

INFO: Welcome to AdvancedOS.
INFO: Main has been scheduled for your convenience
INFO: Adding Assembler process loading to the schedule

INFO: Creating process with PID 1
INFO: Main is yielding to allow something else to run for a bit

INFO: Adding C Process loading to the schedule

INFO: Creating process with PID 2
INFO: System initialisation complete

INFO: Killing process PID:0

INFO: 2 processes ready to be run

INFO: Assigning 42 tickets to process 2

INFO: Assigning 56 tickets to process 1

INFO: Scheduling PID:1

INFO: Creating process with PID 0

INFO: Killing process PID:1

INFO: 2 processes ready to be run

INFO: Assigning 75 tickets to process 2

INFO: Assigning 25 tickets to process 0

INFO: Scheduling PID:2

INFO: Creating process with PID 1

INFO: Killing process PID:2

INFO: 2 processes ready to be run

INFO: Assigning 66 tickets to process 1

INFO: Assigning 33 tickets to process 0

INFO: Scheduling PID:1
Insertion sort took 1080 clock ticks

INFO: Yielding from process PID:1

INFO: 2 processes ready to be run

INFO: Assigning 66 tickets to process 1

INFO: Assigning 33 tickets to process 0

INFO: Scheduling PID:1
Shell sort took 78 clock ticks

INFO: Yielding from process PID:1

INFO: 2 processes ready to be run

INFO: Assigning 66 tickets to process 1

INFO: Assigning 33 tickets to process 0

INFO: Scheduling PID:0

HelloOS assembly test routine starting...

INFO: Creating process with PID 2

HelloOS assembly test routine finished :)

INFO: Killing process PID:0

INFO: 2 processes ready to be run

INFO: Assigning 70 tickets to process 2

INFO: Assigning 28 tickets to process 1

INFO: Scheduling PID:2

Hello World!
INFO: Creating process with PID 0

Hello World done
INFO: Killing process PID:2

INFO: 2 processes ready to be run

INFO: Assigning 28 tickets to process 1

INFO: Assigning 70 tickets to process 0

INFO: Scheduling PID:0

Hello Mars!
INFO: Creating process with PID 2

Hello Mars done
INFO: Killing process PID:0

INFO: 2 processes ready to be run

INFO: Assigning 60 tickets to process 2

INFO: Assigning 40 tickets to process 1

INFO: Scheduling PID:2

Hello Galaxy!
Hello Galaxy done
INFO: Killing process PID:2

INFO: 1 processes ready to be run

INFO: Assigning 100 tickets to process 1

INFO: Scheduling PID:1
Quick sort took 84 clock ticks

INFO: Killing process PID:1

INFO: 0 processes ready to be run

WARN: No process is ready to run
INFO: System is shutting down

INFO: Creating process with PID 0

INFO: Killing process PID:1

INFO: 1 processes ready to be run

INFO: Assigning 100 tickets to process 0

INFO: Scheduling PID:0

INFO: Yielding from process PID:0

INFO: 1 processes ready to be run

INFO: Assigning 100 tickets to process 0

INFO: Scheduling PID:0

</code>

## Appendix B

The source files contain the roughly the following code.

_asm-processes_: assembly processes to load

_c-processes_: c processes to load

_constants.s_: some constants used in assembly land

_demo-programs.c_: simple demonstrative test programs

_interupt-handler.c_: C land interrupt handler

_interupt-shim.s_: Shims for making SVC calls in C land

_ioroutines.c_: as basic OS, but done using printf

_lottery-scheduler.c_: an advanced cooperative scheduler

_main.c_: the start of C code and the first process

_pcb.c_: code for dealing with PCBs (definition in the header)

_schedule.s_: code for loading and yielding from processes

_scheduling.c_: code for scheduling processes

_start.s_: the first initialisation and the shutdown

_system-handler.s_: a shim for SVCs to get into C land as soon as possible

_tables.c_: the allocation of the PCB table (and os-state)

_vectors.s_: interupts and the start of execution


