#ifndef SWITCH_H

#define SWITCH_H

#include "common.h"

enum
{
	sw_released,
	sw_pressed
};

void switch_init(void);
void switch_shut(void);
uint32_t switch_pressed(void);
uint32_t switch_read(void);

#endif
