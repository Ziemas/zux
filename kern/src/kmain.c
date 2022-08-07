#include "dev9.h"
#include "intc.h"
#include "printf.h"
#include "timer.h"
#include "util.h"

void
die(int rate)
{
	int state = 0;

	while (1) {
		udelay(rate);
		dev9_set_led(state);
		state = !state;
	}
}

static void
system_init()
{
	timer_init();
	intc_init();
}

void
kmain()
{
	u32 sp, gp;
	__asm__("move %0, $sp\n" : "=r"(sp) :);
	__asm__("move %0, $gp\n" : "=r"(gp) :);
	printf("hello from kmain at %p\n", kmain);
	printf("   sp: 0x%08x\n", sp);
	printf("   gp: 0x%08x\n", gp);

	system_init();

	die(1000000);
}
