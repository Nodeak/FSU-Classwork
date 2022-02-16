	.data
MSG1:	.asciiz "Hello World!\n"
	.text
	.globl main
main:
	li $s1,7		# Initializes s1 = 7
	li $s2,3		# Initializes s2 = 3
	div $s1,$s2		# Divides $s2 by $s1
	mflo $s1		# $s1 contains quotient
	mfhi $s2		# $s2 contsins remainder
	li $v0,1		# Tell syscall to print an integer
	move $a0,$s1		# Move integer into $a0
	
	syscall

	li $v0,11
	move $a0,$s2

	syscall

	jr $ra