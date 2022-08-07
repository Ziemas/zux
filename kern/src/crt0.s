	.set noreorder
	.globl __start
__start:
	jal __init_reg
	nop
	jal __clearbss
	nop
	j kmain
	nop

__init_reg:
	la $a0, __kern_stack
	addiu $a0, 0x4000
	move $sp, $a0
	la $gp, _gp
	jr $ra
	nop

__clearbss:
	la $v1, __bss_end
	la $v0, __bss_start
	beql $v0, $v1, exit
loop:
	sq $zero, 0($v0)
	addiu $v0, 0x10
	slt $a0, $v1, $v0
	bnel $a0, $zero, loop
exit:
	jr $ra
	nop
