# Solution for the "Fun Practicing with a 2D Array in MIPS Assembly 
# Written by Dr. David A. Gaitros 
# Date: February 1st, 2019 
# Functions:  Printing the Array
#             Accessing individual cells 
#	1. print out all values
#	2. add a break every 9 digits
#	3. put in formatting to make it look pretty
#
#	look for number one in row one and then copy paste the code to check for other numbers
# 	row is offset by 2, column is offset by 18
#
# The first element in the first row is offset 0,0 
# The second element in the first row is offset 0 on the row, and 4 bytes in 
# The first element on the second row, is an offset of 20 on the row, 0 offset on the column 
# The Second element on the second row, is an offset of 20 on the row, and 4 on the column. 
.data

MSG1: 	.asciiz	"9 X 9 Matrix Address Exercise\n"

MSG2:	.asciiz "Enter in a Row #: "

MSG3: 	.asciiz	"Enter is a Column #: "

MSG4:   .asciiz "The Value at that location is: "
EOL:	.byte 	'\n'

SPACES: .asciiz "  "

#MATRIX:	.word	1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9
MATRIX:		.word	1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9, 1, 3, 4, 5, 6, 7, 8, 9, 1, 2, 4, 5, 6, 7, 8, 9, 1, 2, 3, 5, 6, 7, 8, 9, 1, 2, 3, 4, 6, 7, 8, 9, 1, 2, 3, 4, 5, 7, 8, 9, 1, 2, 3, 4, 5, 6, 8, 9, 1, 2, 3, 4, 5, 6, 7, 9, 1, 2, 3, 4, 5, 6, 7, 8
		.text
		.globl main

main:

		li			$v0,4		# Load the $v0 to tell syscall to print a string
		la			$a0,MSG1	# Load the address of the string in $a0
		syscall					# Print the string
		addiu		$sp,$sp,-4	# We get some stack space 
		sw			$ra,0($sp)	# Preserve the return address
	
		jal			PRTMTX		# Call the Print Matrix Subroutin
		lw			$ra,0($sp)	# Restore the return address
		addiu		$sp,$sp,4	# Restore the stack space 

		li			$v0,4		# Print out message to enter row #
		la			$a0,MSG2	# Load address of message
		syscall
		li			$v0,5		# Read an integer
		syscall
		move		$t1,$v0		# Move integer to temp registers
		li			$v0,4		# Print out message to enter col #
		la			$a0,MSG3	# Load address of message
		syscall
		li			$v0,5		# Read an integer
		syscall
		move		$t2,$v0		# Move integer to temp registers
		move		$a0,$t1		# Move Row # to Parameter 1
		move 		$a1,$t2		# Move Col # to Parameter 2
		addiu		$sp,$sp,-4
		sw			$ra,0($sp)
		jal			PRTNUM	
		lw			$ra,0($sp)
		addiu		$sp,$sp,4

		jr			$ra
	
PRTMTX:

		la			$s0,MATRIX	# Load address of Matrix into register $s0
		li			$s1,1		# Row Index - Every four byte
		li			$s2,1 		# Col Index - Every twenty bytes
		li			$t6,9		# Load number of rows and columns

####################################################################################################
# Example:  To get to the address of Row 2, Column 3 I have to perform the following operations.   #
#    Subtract 1 from the row and column number temporarilly.                                       #
#    Multiply the (row-1) * 20  to get the row offset.                                             #
#    Multiply the (col-1) * 4   to get the column offset.                                          #
#    For the first row... and third column , the offset is 0*20 + 2*4  = 8                         #
#################################################################################################### 
TOPPRT: 
	
		addiu		$t1,$s1,-1	# Normalize Row Number to 0-4
		addiu		$t2,$s2,-1	# Normalize Col Number to 0-4
		li			$t4,36		# Size of a row
		li			$t5,4		# Size of a col
		mul			$t1,$t1,$t4	# Get offset of Column
		mul			$t2,$t2,$t5	# Get offset of Row
		add			$s4,$s0,$t1	# Add the Row Offset
		add			$s4,$s4,$t2	# Add the Col Offset
		li			$v0,1		# Print an intege
		lw			$a0,0($s4)	# Load the word
		syscall
		li			$v0,4
		la			$a0,SPACES
		syscall
		li			$t6,9		# Check if we have reached the end.
		div			$s2,$t6		# Divide column number by 5
		mfhi		$t6			# Remainder
		beqz		$t6,ENDROW	# At end of COL
		addiu		$s2,$s2,1	# Add one to the column
		j			TOPPRT		# Get next Number

ENDROW:
		li			$s2,1		# Reset Column Number
		li			$v0,11
		lb			$a0,EOL
		syscall
		li			$t6,9
		div			$s1,$t6		# Divide Row Number by 5,
		mfhi		$t6
		beqz		$t6,DONEPRT
		addiu		$s1,$s1,1	# Add one to row number
		j			TOPPRT

DONEPRT:
		jr			$ra

PRTNUM:
		move		$t1,$a0		# Save Row #
		move		$t2,$a1		# Save Col  #
		addiu		$t1,$t1,-1	# Normalize Row #
		addiu		$t2,$t2,-1	# Normalize Col #
		li			$t3,36		# Size of Row
		mul			$t1,$t1,$t3	# Get Row offset
		li			$t3,4		# Size of Col
		mul			$t2,$t2,$t3	# Get Col offset
		la			$s0,MATRIX	
		add			$s0,$s0,$t1	# Add Row offset to address of Matrix
		add			$s0,$s0,$t2	# Add Col offset to address of Matrix
		li			$v0,4
		la			$a0,MSG4
		syscall
		lw			$a0,0($s0)
		li			$v0,1
		syscall
		jr			$ra

	