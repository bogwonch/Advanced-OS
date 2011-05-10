	PRESERVE8
	AREA AsmProcesses, CODE
	ENTRY
	
	EXPORT init_asm_processes
	IMPORT addNewProcess
	
	IMPORT hello_world
	IMPORT hello_mars
	IMPORT hello_galaxy
	IMPORT HelloOS
	
	ALIGN
ProcessTableStart
	DCD HelloOS
ProcessTableEnd
	DCD 0x0 ; Nil terminated
	ALIGN
	
	;;; Load the processes in the table (why is this not done in C?)
init_asm_processes
	stmfd sp!, {r4,lr}

	ldr r4, =ProcessTableStart
init_asm_loop	
	ldr r0, [r4]
	cmp r0, #0
	beq init_asm_loop_end
	bl addNewProcess
	add r4, r4, #4
	b init_asm_loop
init_asm_loop_end	

	ldmfd sp!, {r4,pc}

	
	END
