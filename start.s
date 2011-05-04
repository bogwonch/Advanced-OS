
	AREA Start, CODE
	ENTRY
	
	IMPORT SVCStack
	IMPORT UserStack
	IMPORT __main
	
	EXPORT System_Init
	EXPORT shutdown_system

	;;; Initialise the system
System_Init
	
	;;; Initialise the System mode and drop into user mode
SVC_System_Init
	ldr sp, =SVCStack
	msr CPSR_c, #0x10
	;b User_System_Init ;; Unnessesary code follows
	
	;;; Initialise the User mode and jump out of Assembly
User_System_Init
	ldr sp, =UserStack
	b __main
	
shutdown_system
	mov r0, #0x18
	ldr r1, =0x20026
	svc 0x123456

	END
	