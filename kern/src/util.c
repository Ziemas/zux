#include "util.h"

#include "cop0.h"

#define CLOCK_RATE 294912000

void
udelay(int u)
{
	u32 delay = ((u64)u) * CLOCK_RATE / 1000000;
	u32 value = mfc0(COP0_R_COUNT);

	while ((mfc0(COP0_R_COUNT) - value) < delay)
		;
}
