	.section .text.init
	.globl __start
__start:
	jal __clearbss
	j kmain

__clearbss:
	jr $ra
