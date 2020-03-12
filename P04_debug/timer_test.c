#include "debug.h"
#include "leds.h"
#include "timer.h"
#include "bbb.h"

int c_entry(void)
{
	debug_init();
	leds_init();

	scan_char();
	print_str_nl("Welcome to SysPlay");

	timer_init(1000);

	for (;;)
	{
		if (TIMER0_IRQSTATUS & (1 << 1))
		{
			TIMER0_IRQSTATUS = (1 << 1);
			leds_toggle(3);
		}
	}

	timer_shut();
	leds_shut();
	debug_shut();

	return 0;
}
