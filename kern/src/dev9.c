#include "dev9.h"

#include "util.h"

#define SPD_REGBASE 0xb4000000
//#define DEV9_REGBASE  0xbf801460
//#define SPD_REGBASE 0x14000000
#define SPD_R_PIO_DIR (SPUD_REGBASE + 0x2c)
#define SPD_R_PIO_DATA (SPD_REGBASE + 0x2e)

void
dev9_set_led(int state)
{
	write8(SPD_R_PIO_DATA, state == 0);
}
