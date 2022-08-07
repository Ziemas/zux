#include "dev9.h"
#include "printf.h"
#include "util.h"

void
die()
{
	int state = 0;

	while (1) {
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		nopdelay();
		dev9_set_led(state);
		state = !state;
	}
}

void
kmain()
{
	u32 sp, gp;
	__asm__("move %0, $sp\n" : "=r"(sp) :);
	__asm__("move %0, $gp\n" : "=r"(gp) :);

	dev9_set_led(0);

	printf("hello from kmain at %p\n", kmain);
	printf("   sp: 0x%08x\n", sp);
	printf("   gp: 0x%08x\n", gp);

	die();
}
