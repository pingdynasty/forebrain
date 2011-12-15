/******************************************************************************
 * Copyright (c) 2011, Universal Air Ltd. All rights reserved.
 * Source and binaries are released under the BSD 3-Clause license
 * See readme_forebrain.txt files for the text of the license
 ******************************************************************************/

#include "LPC13xx.h"
#include "uafunc.h"
#include "config.h"

#define WEAK_ALIAS(f) __attribute__ ((weak, alias (#f)));
#define WEAK __attribute__ ((weak))

// *** some locations provided by the linker
extern void* __stack_top;
extern unsigned long _etext;
extern unsigned long __data;
extern unsigned long __edata;
extern unsigned long __bss;
extern unsigned long __ebss;

// *** these are the user's functions
extern WEAK int main(void);
extern WEAK int setup(void);
extern WEAK int loop(void);

// *** GeneralFault function will flash the LEDs when there is a fault
void GeneralFault(void) {
	volatile unsigned int i;
	LPC_GPIO3->DIR |= 0b1111;
	while(1) {
		for(i=0; i<1000000; i++);
		LPC_GPIO3->DATA = 0b1100;
		for(i=0; i<1000000; i++);
		LPC_GPIO3->DATA = 0b0011;
	}
}

void EmptyFunction(void) {
	return;
}

// *** Alias interrupt handlers to the empty function in case the interrupt
// *** is enabled and no interrupt function is supplied
void I2C_IRQHandler(void)       WEAK_ALIAS(EmptyFunction);
void TIMER16_0_IRQHandler(void) WEAK_ALIAS(EmptyFunction);
void TIMER16_1_IRQHandler(void) WEAK_ALIAS(EmptyFunction);
void TIMER32_0_IRQHandler(void) WEAK_ALIAS(EmptyFunction);
void TIMER32_1_IRQHandler(void) WEAK_ALIAS(EmptyFunction);
void SSP_IRQHandler(void)       WEAK_ALIAS(EmptyFunction);
void UART_IRQHandler(void)      WEAK_ALIAS(EmptyFunction);
void USB_IRQHandler(void)       WEAK_ALIAS(EmptyFunction);
void USB_FIQHandler(void)       WEAK_ALIAS(EmptyFunction);
void ADC_IRQHandler(void)       WEAK_ALIAS(EmptyFunction);
void WDT_IRQHandler(void)       WEAK_ALIAS(EmptyFunction);
void BOD_IRQHandler(void)       WEAK_ALIAS(EmptyFunction);
void FMC_IRQHandler(void)       WEAK_ALIAS(EmptyFunction);
void PIOINT3_IRQHandler(void)   WEAK_ALIAS(EmptyFunction);
void PIOINT2_IRQHandler(void)   WEAK_ALIAS(EmptyFunction);
void PIOINT1_IRQHandler(void)   WEAK_ALIAS(EmptyFunction);
void PIOINT0_IRQHandler(void)   WEAK_ALIAS(EmptyFunction);
void WAKEUP_IRQHandler(void)    WEAK_ALIAS(EmptyFunction);
void SysTick_Handler(void)      WEAK_ALIAS(EmptyFunction);

void NMI_Handler(void)          WEAK_ALIAS(GeneralFault);
void HardFault_Handler(void)    WEAK_ALIAS(GeneralFault);
void MemManage_Handler(void)    WEAK_ALIAS(GeneralFault);
void BusFault_Handler(void)     WEAK_ALIAS(GeneralFault);
void UsageFault_Handler(void)   WEAK_ALIAS(GeneralFault);
void SVCall_Handler(void)       WEAK_ALIAS(GeneralFault);
void DebugMon_Handler(void)     WEAK_ALIAS(GeneralFault);
void PendSV_Handler(void)       WEAK_ALIAS(GeneralFault);


// *** This is the startup code
void Reset_Handler(void) {
	unsigned long *pSrc, *pDest;

	// Initialise RAM
	pSrc = &_etext;
	for(pDest=&__data; pDest<&__edata; ) {
	  *pDest++ = *pSrc++;
	}

	for(pDest=&__bss; pDest<&__ebss; ) {
	  *pDest++ = 0;
	}
	
	// Initialise the uninitialised variable described in section 19.2.1 of UM10365
	*((uint32_t *)(0x10000054)) = 0x0;
	
    // Set clock mode, DEFAULT_CLOCK is defined in config.h, and the default behaviour
    // is to set the clock to 72MHz from the external crystal.
    ClockMode(DEFAULT_CLOCK);

    // Set all pins to digital inputs (except P0[0] which is the reset button)
	Port0Init(ALL & ~PIN0);	
	Port1Init(ALL);
	Port2Init(ALL);
	Port3Init(ALL);

    // Initialise and start the system tick timer if allowed by the SYSTICK_EN
    // definition in config.h, if the system tick timer is running, then the Delay()
    // function will use it, otherwise Delay() will use a fixed loop which is not
    // accurate when there are interrupts running, as any interrupt would stop the
    // loop and cuase the delay to be longer than expected
	#if SYSTICK_EN
		SysTickInit();
	#endif
	
    // Run the user-supplied setup() function if it exists
	if(setup) {
		setup();
	}
    
    // Run the user-supplied main() function if it exists
	if(main) {
		main();
	}
    
    // Loop the user-supplied setup() function if it exists
	if(loop) {
		while(1) loop();
	}
    
    // Do nothing (except handle interrupts)
	while(1);
}

// *** Vector table
__attribute__ ((section(".vectors"), used))
const void *vectors[] =
{
	&__stack_top,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0, 0, 0, 0,
	SVCall_Handler,
	DebugMon_Handler, 
	0,
	PendSV_Handler,
	SysTick_Handler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	WAKEUP_IRQHandler,
	I2C_IRQHandler,
	TIMER16_0_IRQHandler,
	TIMER16_1_IRQHandler,
	TIMER32_0_IRQHandler,
	TIMER32_1_IRQHandler,
	SSP_IRQHandler,
	UART_IRQHandler,
	USB_IRQHandler,
	USB_FIQHandler,
	ADC_IRQHandler,
	WDT_IRQHandler,
	BOD_IRQHandler,
	FMC_IRQHandler,
	PIOINT3_IRQHandler,
	PIOINT2_IRQHandler,
	PIOINT1_IRQHandler,
	PIOINT0_IRQHandler,
};