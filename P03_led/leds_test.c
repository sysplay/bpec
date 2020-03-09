#include "leds.h"
#include "common.h"

// Four LEDs, 0x0-0xF
#define LEDS_PATTERN (0x1)

static void leds_pattern_toggle(uint8_t pattern)
{
	if (pattern & 0x1) leds_toggle(0);
	if (pattern & 0x2) leds_toggle(1);
	if (pattern & 0x4) leds_toggle(2);
	if (pattern & 0x8) leds_toggle(3);
}
static void heartbeat_forever(void)
{
	for (;;)
	{
		// On
		leds_pattern_toggle(LEDS_PATTERN);
		delay(500000);

		// Off
		leds_pattern_toggle(LEDS_PATTERN);
		delay(380000);

		// On
		leds_pattern_toggle(LEDS_PATTERN);
		delay(240000);

		// Off
		leds_pattern_toggle(LEDS_PATTERN);
		delay(2400000);
	}
}

int c_entry(void)
{
	leds_init();

	heartbeat_forever();

	leds_shut();

	return 0;
}
