#include "timer.h"

#include "printf.h"
#include "types.h"
#include "util.h"

#define NUM_TIMERS 4
#define TIMER_ADDR_OFFSET 0x800
#define TIMER_BASE 0xB0000000
#define TIMER_COUNT 0x0
#define TIMER_MODE 0x10
#define TIMER_CLOCK GENMASK(1, 0)
#define TIMER_GATE_ENABLE BIT(2)
#define TIMER_GATE_TYPE BIT(3)
#define TIMER_GATE_MODE GENMASK(5, 4)
#define TIMER_ROLLOVER_RESET BIT(6)
#define TIMER_ENABLE BIT(7)
#define TIMER_COMP_INTR BIT(8)
#define TIMER_OVERFLOW_INTR BIT(9)

#define TIMER_COMP 0x20
#define TIMER_HOLD 0x30

struct timer_dev {
	uintptr_t regs;
};

struct timer_dev timer[4] = {};

extern void die(int);

void
timer_init(void)
{
	printf("-- TIMER_INIT --\n");
	for (int i = 0; i < NUM_TIMERS; i++) {
		timer[i].regs = TIMER_BASE + (TIMER_ADDR_OFFSET * i);
		clear32(timer[i].regs + TIMER_MODE, TIMER_ENABLE);
		clear32(timer[i].regs + TIMER_MODE, TIMER_COMP_INTR);
		clear32(timer[i].regs + TIMER_MODE, TIMER_OVERFLOW_INTR);
		clear32(timer[i].regs + TIMER_MODE, TIMER_GATE_ENABLE);
		clear32(timer[i].regs + TIMER_MODE, TIMER_ROLLOVER_RESET);

		write32(timer[i].regs + TIMER_COMP, 0);
		write32(timer[i].regs + TIMER_HOLD, 0);
	}

	// mask32(timer[0].regs + TIMER_MODE, TIMER_CLOCK,
	//     FIELD_PREP(TIMER_CLOCK, 0));
	// mask32(timer[0].regs + TIMER_MODE, TIMER_GATE_MODE,
	//     FIELD_PREP(TIMER_GATE_MODE, 0));

	// set32(timer[0].regs + TIMER_MODE, TIMER_ENABLE);
}
