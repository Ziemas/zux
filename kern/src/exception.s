#	.set noreorder
	.section .vec.tlb.el0
__excep_tlb_el0:
	nop
	nop
	nop
	j __excep_tlb_el0
	nop

	.section .vec.irq
__excep_irq:
	nop
	nop
	nop
	j __excep_irq
	nop

	.section .vec.other
__excep_other:
	nop
	nop
	nop
	j __excep_other
	nop

	.section .vec.perfc
__excep_perfc:
	nop
	nop
	nop
	j __excep_perfc
	nop

	.section .vec.debug
__excep_debug:
	nop
	nop
	nop
	j __excep_debug
	nop
