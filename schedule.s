	AREA Schedule, CODE
	
	EXPORT schedule_process
	EXPORT save_yielded

	IMPORT Kill

	; void save_yielded(PCB *proc, void *return)
save_yielded
	stmfd sp!, {r4, lr}
	
	; Save the registers in the PCB
	add r0, r0, #24
	
	;str r1, [r0], #4
	;str r2, [r0], #4
	;str r3, [r0], #4
	str r4, [r0], #4
	str r5, [r0], #4
	str r6, [r0], #4
	str r7, [r0], #4
	str r8, [r0], #4
	str r9, [r0], #4
	str r10,[r0], #4
	str r11,[r0], #4
	str ip, [r0], #4
	
	msr CPSR_c, #0x1f
	str sp, [r0], #4
	str lr, [r0], #8
	mrs r2, CPSR
	str r2, [r0], #-4
	msr CPSR_c, #0xd3
	
	
	str r1, [r0] ; Save the PC for the jump back

	ldmfd sp!, {r4, pc}
	
	; void schedule_process(PCB *proc)
schedule_process
	; r0 contains PCB we want to jump into.

	; Drop to user mode
	msr CPSR_c, #0x10	
	
	; Move the LR to the start of the Regs
	add r0, r0, #24
	
	;LDR r0, [ip], #4
	;LDR r1, [ip], #4
	;LDR r2, [ip], #4
	;LDR r3, [ip], #4
	LDR r4, [r0], #4
	LDR r5, [r0], #4
	LDR r6, [r0], #4
	LDR r7, [r0], #4
	LDR r8, [r0], #4
	LDR r9, [r0], #4
	LDR r10,[r0], #4
	LDR r11,[r0], #4
	LDR ip, [r0], #4
	LDR sp, [r0], #4
	LDR lr, [r0], #8
	LDR r1, [r0], #-4
	msr CPSR_cxsf, r1
	LDR pc, [r0]
	
		

	
	END
	
