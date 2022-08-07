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
DIntr()
{
	int eie, res;

	asm volatile("mfc0 %0, $12" : "=r"(eie));
	eie &= 0x10000;
	res = eie != 0;

	if (!eie)
		return 0;

	asm(".p2align 3");
	do {
		asm volatile("di\n"
			     "sync.p\n"
			     "mfc0\t%0, $12\n"
			     : "=r"(eie));
		eie &= 0x10000;
	} while (eie);

	return res;
}

static inline int
EIntr()
{
	int eie;

	asm volatile("mfc0 %0, $12" : "=r"(eie));
	eie &= 0x10000;
	asm volatile("ei");

	return eie != 0;
}

static inline int
ee_kmode_enter()
{
	u32 status, mask;

	__asm__ volatile(".set push\n"
			 ".set noreorder\n"
			 "mfc0 %0, $12\n"
			 "li %1, 0xffffffe7\n"
			 "and %0, %1\n"
			 "mtc0 %0, $12\n"
			 "sync.p\n"
			 ".set pop\n"
			 : "=r"(status), "=r"(mask));

	return status;
}

static inline int
ee_kmode_exit()
{
	int status;

	__asm__ volatile(".set push\n"
			 ".set noreorder\n"
			 "mfc0 %0, $12\n"
			 "ori %0, 0x10\n"
			 "mtc0 %0, $12\n"
			 "sync.p\n"
			 ".set pop\n"
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

static inline u32
set32(u32 addr, u32 set)
{
	u32 data;
	__asm__ volatile("lw %0, 0(%1)\n"
			 "or %0, %2\n"
			 "sw %0, 0(%1)\n"
			 : "=&r"(data)
			 : "r"(addr), "r"(set)
			 : "memory");
	return data;
}

static inline u32
clear32(u32 addr, u32 clear)
{
	u32 data;
	__asm__ volatile("lw %0, 0(%1)\n"
			 "not %2\n"
			 "and %0, %2\n"
			 "sw %0, 0(%1)\n"
			 : "=&r"(data)
			 : "r"(addr), "r"(clear)
			 : "memory");
	return data;
}

static inline u32
mask32(u32 addr, u32 clear, u32 set)
{
	u32 data;
	__asm__ volatile(".set noat\n"
			 "lw %0, 0(%1)\n"
			 "not %3\n"
			 "and %0, %3\n"
			 "or $0, %2\n"
			 "sw $0, 0($1)\n"
			 : "=&r"(data)
			 : "r"(addr), "r"(set), "r"(clear)
			 : "memory");
	return data;
}

static inline u16
read16(u32 addr)
{
	u8 data;
	__asm__ volatile("lh %0, 0(%1)" : "=r"(data) : "r"(addr) : "memory");
	return data;
}

static inline void
write16(u32 addr, u16 data)
{
	__asm__ volatile("sh %0, 0(%1)" : : "r"(data), "r"(addr) : "memory");
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

static inline int
poll32(u32 addr, u32 mask, u32 target)
{
	while (1) {
		u32 value = read32(addr) & mask;
		if (value == target) {
			return 0;
		}
	}
}

#define _mfc0(reg)                                                            \
	({                                                                    \
		u32 val;                                                      \
		__asm__ volatile("mfc0 %0, " #reg "\n sync.l\n" : "=r"(val)); \
		val;                                                          \
	})

static inline void
nopdelay(void)
{
	int i = 0xfffff;

	do {
		__asm__("nop\nnop\nnop\nnop\nnop\n");
	} while (i-- != -1);
}

#endif // UTIL_H_
