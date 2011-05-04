		; HelloOS test file for COMS35102 Advanced OS
		; uses nested processes, that need to be supported by the OS
		
		AREA HelloOSTest, CODE, READONLY

		EXPORT HelloOS ; symbol for linking to the OS

HelloOS
		ADR r0, HelloOStext
		SVC 0x04; print zero-terminated string
		ADR r0, HelloWorld
		SVC 0x05 ; create process
		ADR r0, HelloOSdone
		SVC 0x04
		SVC 0x00 ; terminate process

HelloWorld
		ADR	r0, Hellotext
		SVC 0x04 ; print zero-terminated string
		ADR r0, HelloMars
		SVC 0x05 ; create nested process
		ADR r0, Hellodone
		SVC 0x04
		SVC 0x00 ; terminate process

HelloMars
		ADR	r0, HelloMtext
		SVC 0x04 ; print zero-terminated string
		ADR	r0, HelloGalaxy
		SVC 0x05 ; create nested process
		ADR r0, HelloMdone
		SVC 0x04
		SVC 0x00 ; terminate process

		
HelloGalaxy
		ADR	r0, HelloGtext
		SVC 0x04 ; print zero-terminated string
		ADR r0, HelloGdone
		SVC 0x04
		SVC 0x00 ; terminate process		




		; DATA CONSTANTS

HelloOStext
		DCB		  "\nHelloOS assembly test routine starting...\n",0

Hellotext
        DCB       "\nHello World!",0
        
HelloMtext
        DCB       "\nHello Mars!",0
        
HelloGtext
        DCB       "\nHello Galaxy!",0
      
HelloOSdone
		DCB		  "\nHelloOS assembly test routine finished :)\n",0
        
Hellodone
        DCB       "\nHello World done",0
        
HelloMdone
        DCB       "\nHello Mars done",0
        
HelloGdone
        DCB       "\nHello Galaxy done",0
        
        END