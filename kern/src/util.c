#include "util.h"

#include "cop0.h"

#define CLOCK_RATE 294912000

void
udelay(int u)
{
	u32 delay = ((u64)u) * CLOCK_RATE / 1000000;
	u32 value = mfc0(COUNT);

	while ((mfc0(COUNT) - value) < delay)
		;
}
