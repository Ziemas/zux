#include "dev9.h"
#include "printf.h"
#include "util.h"

void
kmain()
{
	ee_kmode_enter();
	printf("Kernel Main\n");

	while (1)
		;
}
