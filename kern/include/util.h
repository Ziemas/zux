#ifndef UTIL_H_
#define UTIL_H_

#include "types.h"

// Borrowed from m1n1
#define BIT(x) (1UL << (x))
#define MASK(x) (BIT(x) - 1)
#define GENMASK(msb, lsb) ((BIT((msb + 1) - (lsb)) - 1) << (lsb))
#define _FIELD_LSB(field) ((field) & ~(field - 1))
#define FIELD_PREP(field, val) ((val) * (_FIELD_LSB(field)))
#define FIELD_GET(field, val) (((val) & (field)) / _FIELD_LSB(field))

#define ALIGN_UP(x, a) (((x) + ((a)-1)) & ~((a)-1))
#define ALIGN_DOWN(x, a) ((x) & ~((a)-1))

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

static inline int
ee_kmode_enter()
{
	u32 status, mask;

	__asm__ volatile(".set\tpush\n\t"
			 ".set\tnoreorder\n\t"
			 "mfc0\t%0, $12\n\t"
			 "li\t%1, 0xffffffe7\n\t"
			 "and\t%0, %1\n\t"
			 "mtc0\t%0, $12\n\t"
			 "sync.p\n\t"
			 ".set\tpop\n\t"
			 : "=r"(status), "=r"(mask));

	return status;
}

static inline int
ee_kmode_exit()
{
	int status;

	__asm__ volatile(".set\tpush\n\t"
			 ".set\tnoreorder\n\t"
			 "mfc0\t%0, $12\n\t"
			 "ori\t%0, 0x10\n\t"
			 "mtc0\t%0, $12\n\t"
			 "sync.p\n\t"
			 ".set\tpop\n\t"
			 : "=r"(status));

	return status;
}

static inline u32
read32(u32 addr)
{
	u32 data;
	__asm__ volatile("lw %0, 0(%1)" : "=r"(data) : "r"(addr) : "memory");
	return data;
}

static inline void
write32(u32 addr, u32 data)
{
	__asm__ volatile("sw %0, 0(%1)" : : "r"(data), "r"(addr) : "memory");
}

static inline u8
read8(u32 addr)
{
	u8 data;
	__asm__ volatile("lb %0, 0(%1)" : "=r"(data) : "r"(addr) : "memory");
	return data;
}

static inline void
write8(u32 addr, u8 data)
{
	__asm__ volatile("sb %0, 0(%1)" : : "r"(data), "r"(addr) : "memory");
}

#endif // UTIL_H_
