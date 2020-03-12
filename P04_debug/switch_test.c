#include "debug.h"
#include "leds.h"
#include "switch.h"

int c_entry(void)
{
	debug_init();
	leds_init();

	scan_char();
	print_str_nl("Welcome to SysPlay");

	switch_init();

	for (;;)
	{
		if (switch_pressed())
		{
			print_str("Switch: ");
			if (switch_read() == sw_released)
				print_str_nl("Released");
			else
				print_str_nl("Pressed");

			leds_toggle(0);
		}
	}

	switch_shut();
	leds_shut();
	debug_shut();

	return 0;
}
