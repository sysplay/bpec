#include "bbb.h"
#include "arm.h"
#include "common.h"
#include "interrupt.h"

#define MAX_NUM_IRQS 128
#define IRQ_MASK ((MAX_NUM_IRQS) - 1)

static void (*ivt[MAX_NUM_IRQS])(void); // Make no assumptions on its NULL initialization

void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
	while (1)
	{
		/* Do Nothing! */
	}
}
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
	while (1)
	{
		/* Do Nothing! */
	}
}
void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
	while (1)
	{
		/* Do Nothing! */
	}
}
void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{
	while (1)
	{
		/* Do Nothing! */
	}
}
void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
	uint8_t irq = (INTC_SIR_IRQ & IRQ_MASK);

	if (ivt[irq])
	{
		/* TODO 2: Call the interrupt handler */
	}
	mb(); // Data Sync Barrier
	INTC_CONTROL = (1 << 0); // Let next IRQ trigger
}
void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{
	/* Do Nothing as not supported on BBB! */

	mb(); // Data Sync Barrier
	INTC_CONTROL = (1 << 1); // Let next FIQ trigger
}

static void setup_ivt(void)
{
	int i;
	void (**public_ram)(void) = (void (**)(void))(0x4030CE20);
	extern void _undefined_instruction(void);
	extern void _software_interrupt(void);
	extern void _prefetch_abort(void);
	extern void _data_abort(void);
	extern void _interrupt(void);
	extern void _fast_interrupt(void);

	/* Nullify our IVT, not depending on BSS */
	for (i = 0; i < MAX_NUM_IRQS; i++)
		ivt[i] = NULL;

	/* Initialization - Sec 26 */
	/*
	 * Reset			- 0x20000 - 0x402F0400 // Internal SRAM start
	 * 							  - 0x4030B800 // Stack
	 * Undefined		- 0x20004 - 0x4030CE04 <- 0x4030CE24
	 * SWI				- 0x20008 - 0x4030CE08 <- 0x4030CE28
	 * Pre-fetch abort	- 0x2000C - 0x4030CE0C <- 0x4030CE2C
	 * Data abort		- 0x20010 - 0x4030CE10 <- 0x4030CE30
	 * Unused			- 0x20014 - 0x4030CE14 <- 0x4030CE34
	 * IRQ				- 0x20018 - 0x4030CE18 <- 0x4030CE38
	 * FRQ				- 0x2001C - 0x4030CE1C <- 0x4030CE3C
	 * 							  - 0x4030FFFF // Internal SRAM end
	 */

	//public_ram[0] = 
	public_ram[1] = _undefined_instruction;
	public_ram[2] = _software_interrupt;
	public_ram[3] = _prefetch_abort;
	public_ram[4] = _data_abort;
	//public_ram[5] = 
	public_ram[6] = NULL /* TODO 3: Fill in the interrupt handler from assembly */;
	public_ram[7] = _fast_interrupt;
}

void interrupt_init(void)
{
	setup_ivt();
	mb(); // Data Sync Barrier
	// Enable IRQ at ARM Core side
	// Refer sec 2.14 in Cortex A8 TRM
	__asm__ __volatile__("mrs r0, cpsr\n");
	__asm__ __volatile__("bic r0, r0, 0x80\n"); // 0x80 for IRQ, 0x40 for FIQ
	__asm__ __volatile__("msr cpsr, r0\n");
}
void interrupt_shut(void)
{
	mb(); // Data Sync Barrier
	// Disable IRQ at ARM Core side
	// Refer sec 2.14 in Cortex A8 TRM
	__asm__ __volatile__("mrs r0, cpsr\n");
	__asm__ __volatile__("orr r0, r0, 0x80\n"); // 0x80 for IRQ, 0x40 for FIQ
	__asm__ __volatile__("msr cpsr, r0\n");
}

void interrupt_enable(uint8_t irq)
{
	switch (irq >> 5) // / 32
	{
		case 0:
			INTC_MIR_CLEAR0 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
		case 1:
			INTC_MIR_CLEAR1 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
		case 2:
			INTC_MIR_CLEAR2 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
		case 3:
			INTC_MIR_CLEAR3 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
	}
}
void interrupt_disable(uint8_t irq)
{
	switch (irq >> 5) // / 32
	{
		case 0:
			INTC_MIR_SET0 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
		case 1:
			INTC_MIR_SET1 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
		case 2:
			INTC_MIR_SET2 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
		case 3:
			INTC_MIR_SET3 = 1 << (irq & ((1 << 5) - 1)); // % 32
			break;
	}
}

void interrupt_handler_register(uint8_t irq, void (*handler)(void))
{
	ivt[irq] = handler;
	INTC_ILR(irq) = (0 << 2) | (0 << 0);
	interrupt_enable(irq);
}
void interrupt_handler_unregister(uint8_t irq)
{
	interrupt_disable(irq);
	INTC_ILR(irq) = 0;
	ivt[irq] = NULL;
}
