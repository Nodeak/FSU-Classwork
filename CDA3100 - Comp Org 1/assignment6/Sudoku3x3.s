	.data
###########################################################
# Sample Print 3x3 Puzzle                                 #
#     -------                                             #
#     |1|2|3|                                             #
#     -------                                             #
#     |2|3|1|                                             #
#     -------                                             #
#     |3|1|2|                                             #
#     -------                                             #
#  A sample program on how to (1) Call a subroutin        #
#  (2) Pass a paramter, and (3) print a 2 d array.        #
# Author:  Dr. David A. Gaitros                           #
# Date:  October 15, 2018                                 # 
###########################################################
MSG1: 	.asciiz "Sample Print 3x3 Puzzle\n"
PUZZLE:	.asciiz	"1 2 3 4 5 6 7 8 9 2 3 4 5 6 7 8 9 1 3 4 5 6 7 8 9 1 2 4 5 6 7 8 9 1 2 3 5 6 7 8 9 1 2 3 4 6 7 8 9 1 2 3 4 5 7 8 9 1 2 3 4 5 6 8 9 1 2 3 4 5 6 7 9 1 2 3 4 5 6 7 8"
UNDER:	.asciiz "-------\n"
BAR:	.byte	'|'
EOL:	.byte 	'\n'
	.align 2
	.text
	.globl main
main:
	la	$a0,PUZZLE	# Load address of puzzle in $a0
	addiu	$sp,$sp,-4	# Get space from the stack
	sw	$ra,0($sp)	# Store return address
	jal	PRTPZL		# Call the routine PRTPZL
	lw	$ra,0($sp)	# Load return addres
	addiu	$sp,$sp,4	# Return space to the stack
	jr	$ra

PRTPZL: 
	move	$s0,$a0		# Preserve parameter 
	li	$s1,9		# Set up Counter
	li	$v0,4		# Print a String
	la	$a0,MSG1	# Load Message
	syscall
TOP:	
	beq	$s1,$zero,DONE	# Branch to DONE if counter is zero
	li	$v0,4		# Tell syscal to print a string
	la	$a0,UNDER	# Print underscore
	syscall 		# 

	li	$v0,11		# Print vertical bar
	lb	$a0,BAR		# Load the BAR
	syscall
	li	$v0,11		# Tell syscall to print a character
	lb	$a0,0($s0)	# Print first number in row
	syscall 
	li	$v0,11		# Print vertical bar
	lb	$a0,BAR		# Load the BAR
	syscall
	li	$v0,11		# Tell syscall to load a byte
	lb	$a0,2($s0)	# Print second number in row
	syscall 
	li	$v0,11		# Print vertical bar
	lb	$a0,BAR		# Load the BAR
	syscall
	li	$v0,11		# Tell syscall to print a character
	lb	$a0,4($s0)	# Print third number in row
	syscall 
	li	$v0,11		# Tell syscall to print a character
	lb	$a0,BAR		# Load the BAR
	syscall
	li	$v0,11		# Tell syscall to print a character
	lb	$a0,EOL		# Print end of line
	syscall
	addiu	$s0,$s0,6	# Get next row
	addiu	$s1,$s1,-1	# Subtract from counter
	j	TOP
DONE:
	li	$v0,4
	la	$a0,UNDER
	syscall 
	jr	$ra
