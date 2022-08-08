#ifndef COP0_H_
#define COP0_H_

#define BAD_VADDR $9
#define COUNT $9
#define COMPARE $11
#define STATUS $12
#define CAUSE $13
#define EPC $14
#define PRID $15
#define CONFIG $16
#define BAD_PADDR $23

#define _mfc0(reg)                                              \
	({                                                      \
		u32 val;                                        \
		__asm__ volatile("mfc0 %0, " #reg : "=r"(val)); \
		val;                                            \
	})

#define mfc0(reg) _mfc0(reg)

#define _mtc0(reg)                                                           \
	({                                                                   \
		u32 val;                                                     \
		__asm__ volatile("mtc0 %0, " #reg "\n sync.p\n" : "r"(val)); \
		val;                                                         \
	})

#define mtc0(reg) _mtc0(reg)

#endif // COP0_H_
