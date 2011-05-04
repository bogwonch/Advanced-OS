	AREA SystemHandler, CODE
	ENTRY
	
	EXPORT System_Handler
	IMPORT interupt_handler

	
	;;; Software interupt handler
System_Handler
	stmfd sp!, {r0-r3,r12,lr}
	mov r3, r0
	
	mov r1, sp
	mrs r0, SPSR
	stmfd sp!, {r0,r3}
	
	tst r0, #0x20
	ldrhne r0, [lr,#-2]
	bicne r0, r0, #0xFF00
	biceq r0, r0, #0xFF000000
	
	; Get the interupt ID
	ldr r0, [lr, #-4]
	and r0, r0, #0xFFFFFF
	
	; If yielding pass the link address, else pass any argument
	cmp r0, #11
	moveq r1, lr
	movne r1, r3
	
	bl interupt_handler
	
	ldmfd sp!, {r0, r3}
	msr SPSR_cf, r0
	ldmfd sp!, {r0-r3,r12,pc}^
	
	END