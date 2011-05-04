	AREA Vectors, CODE
	ENTRY
	
	EXPORT Interupt_Vector_Table
	
	IMPORT System_Init
	IMPORT System_Handler
	
	
Interupt_Vector_Table
	b System_Init
	nop
	b System_Handler
	nop
	nop
	nop
	nop
	nop
	
	
	END