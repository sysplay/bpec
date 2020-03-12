#include "bbb.h"
#include "switch.h"

#define SWITCH_MASK (1 << 8)

void switch_init(void)
{
	// Enable the GPIO2 clock
	CM_PER_GPIO2_CLKCTRL = (0x1 << 18) | (0x2 << 0);

	// Enable input
	//GPIO1_OE |= LED_MASK; // Default option

	// Enable debouncing
	//GPIO2_DEBOUNCINGTIME = 0xFF; // Max possible - approx 8ms
	//GPIO2_DEBOUNCENABLE |= SWITCH_MASK;

	// Set edge trigger
	GPIO2_FALLINGDETECT |= SWITCH_MASK; // Press
	GPIO2_RISINGDETECT |= SWITCH_MASK; // Release

	// Enable trigger
	GPIO2_IRQSTATUS_SET_0 = SWITCH_MASK;
}
void switch_shut(void)
{
	// Disable trigger
	GPIO2_IRQSTATUS_CLR_0 = SWITCH_MASK;

	// Clear edge trigger
	GPIO2_RISINGDETECT &= ~SWITCH_MASK;
	GPIO2_FALLINGDETECT &= ~SWITCH_MASK;

	// Disable debouncing
	//GPIO2_DEBOUNCENABLE &= ~SWITCH_MASK;
	//GPIO2_DEBOUNCINGTIME = 0;

	// Disable the GPIO2 clock
	CM_PER_GPIO2_CLKCTRL = 0; // Problem in case others using GPIO2
}
uint32_t switch_pressed(void)
{
	uint32_t st = !!(GPIO2_IRQSTATUS_0 & SWITCH_MASK);

	GPIO2_IRQSTATUS_0 = SWITCH_MASK;
	return st;
}
uint32_t switch_read(void)
{
	return !(GPIO2_DATAIN & SWITCH_MASK);
}
