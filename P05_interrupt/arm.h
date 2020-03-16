#ifndef ARM_H

#define ARM_H

static inline void mb(void)
{
	__asm__ __volatile__("dsb\n");
}
static inline void ib(void)
{
	__asm__ __volatile__("isb\n");
}

#endif
