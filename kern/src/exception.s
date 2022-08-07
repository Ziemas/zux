	.set noreorder
	.text
	.globl __dead_loop
	.extern die
__dead_loop:
	li $a0, 400000
	jal die
	nop
	nop
	nop
	nop
	b __dead_loop

	.section .vec.tlb.el0
__excep_tlb_el0:
	j __dead_loop
	nop

	.section .vec.irq
__excep_irq:
	j __dead_loop
	nop

	.section .vec.other
__excep_other:
	j __dead_loop
	nop

	.section .vec.perfc
__excep_perfc:
	j __dead_loop
	nop

	.section .vec.debug
__excep_debug:
	j __dead_loop
	nop
