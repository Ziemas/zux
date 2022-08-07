#include "util.h"

#define CLOCK_RATE 294912000

void
udelay(int u)
{
	u64 delay = ((u64)u) * CLOCK_RATE / 1000000;
	u32 value = _mfc0($9);

	while ((_mfc0($9) - value) < delay)
		;
}
