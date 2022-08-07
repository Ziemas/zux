MEMORY
{
	vec (rx) : org = 0x80000000, len = 4k
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

	.data ALIGN(128) : {
		*(.data)
		*(.rodata)
		*(.rodata.*)
	} > ram

	_gp = ALIGN(128);

	.bss ALIGN(128) : {
		PROVIDE(__bss_start = .);
		*(.bss)
		PROVIDE(__bss_end = .);
	} > ram

	PROVIDE(__kern_stack = ALIGN(128));

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
