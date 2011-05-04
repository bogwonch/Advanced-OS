	AREA InteruptShim, CODE
	;;;; Contains functions which can be used to call an interupt from C code
	
	EXPORT addNewProcess
	EXPORT Kill
	EXPORT Shutdown
	EXPORT Yield
	
	; int addNewProcess(int (*) void)
addNewProcess
	stmfd sp!, {r4,lr}
	svc #10
	ldmfd sp!, {r4,pc}
	
Kill
	svc #0
	
Shutdown
	svc #0xD13
	
Yield
	svc #11
	mov pc, lr
	
	
	END