	PRESERVE8
	AREA Start, CODE
	ENTRY
	
	IMPORT SVCStack
	IMPORT __main
	IMPORT addNewProcess
	IMPORT pcb_table
	;IMPORT init_pcb_table
	IMPORT schedule_next
	
	EXPORT System_Init
	EXPORT shutdown_system

	;;; Initialise the system
System_Init
SVC_System_Init
	ldr sp, =SVCStack  ; 
	bl init_pcb_table
	ldr r0, =__main
	bl addNewProcess
	b schedule_next
		
shutdown_system
	; last chance to yield...
	svc #11
	mov r0, #0x18
	ldr r1, =0x20026
	svc 0x123456
	
init_pcb_table
	stmfd sp!, {r4,lr}
	
	ldr r0, =pcb_table
	add r0, r0, #4 ; move to the state field
	mov r1, #64    ; how many PCBs to initialise
	mov r2, #0     ; what to initialise the state field with
	ldr r3, =16464 ; 4*sizeof(PCB) offset between each of them
ipcb_loop
	str r2, [r0]
	add r0, r0, r3
	subs r1, r1, #1
	bne ipcb_loop	
	
	ldmfd sp!, {r4, pc}

	END
	
