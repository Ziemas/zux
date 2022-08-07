#ifndef COP0_H_
#define COP0_H_

#define COP0_R_COUNT "$9"

#define mfc0(reg)                                                             \
	({                                                                    \
		u32 val;                                                      \
		__asm__ volatile("mfc0 %0, " reg "\n sync.l\n" : "=r"(val)); \
		val;                                                          \
	})

#endif // COP0_H_
