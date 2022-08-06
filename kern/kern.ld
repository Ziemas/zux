MEMORY
{
	vec (wx) : org = 0x80000000, len = 4k
	ram (wx) : org = 0x80001000, len = 128k
}

SECTIONS
{
	.text 0x80000000 : { *(.vec.tlb.el0) } > vec
	.text 0x80000080 : { *(.vec.perfc) } > vec
	.text 0x80000100 : { *(.vec.debug) } > vec
	.text 0x80000180 : { *(.vec.other) } > vec
	.text 0x80000200 : { *(.vec.irq) } > vec

	.text  : {
		*(.text.init)
		*(.text)
	} > ram

	.data : {
		*(.data)
		*(.rodata)
		*(.rodata.*)
	} > ram

	.bss : {
		PROVIDE(__bss_start = .);
		*(.bss)
		PROVIDE(__bss_end = .);
	} > ram

	/DISCARD/ : {
		*(.debug*)
		*(.mdebug*)
		*(.gnu.attributes)
		*(.pdr)
		*(.comment)
		*(.MIPS.abiflags)
		*(.reginfo)
	}
}
