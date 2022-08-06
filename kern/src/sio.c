#include "sio.h"

#include "types.h"
#include "util.h"

//#define SIO_ISR 0xb000f130
//#define SIO_TXFIFO 0xb000f180


#define SIO_ISR 0x1000f130
#define SIO_TXFIFO 0x1000f180

void
sio_init()
{
}

void
sio_putchar(int c)
{
	while ((read32(SIO_ISR) & 0xf000) == 0x8000)
		;

	write8(SIO_TXFIFO, c);
}
