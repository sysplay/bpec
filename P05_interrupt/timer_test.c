#include "debug.h"
#include "leds.h"
#include "timer.h"
#ifdef INTR_BASED_TIMER
#include "interrupt.h"
#endif
#include "bbb.h"

#ifdef INTR_BASED_TIMER
void handler(void)
{
	TIMER0_IRQSTATUS = (1 << 1);
	leds_toggle(3);
}
#endif

int c_entry(void)
{
	debug_init();
	leds_init();

	scan_char();
	print_str_nl("Welcome to SysPlay");

#ifdef INTR_BASED_TIMER
	interrupt_init();
	timer_handler_register(handler);
#endif
	timer_init(1000);

	for (;;)
	{
#ifdef INTR_BASED_TIMER
		delay(1000);
#else
		if (TIMER0_IRQSTATUS & (1 << 1))
		{
			TIMER0_IRQSTATUS = (1 << 1);
			leds_toggle(3);
		}
#endif
	}

	timer_shut();
#ifdef INTR_BASED_TIMER
	timer_handler_unregister();
	interrupt_shut();
#endif
	leds_shut();
	debug_shut();

	return 0;
}
