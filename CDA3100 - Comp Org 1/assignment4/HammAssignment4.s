#################################################
#			Kaedon Hamm							#
#	Class:	CDA 3100							#
#	Date:	2.15.2019							#
#	Assignment: Read in two numbers and find,	#
#				the sum, difference, product,	#
#				and quotient/remainder of them	#
#################################################



		.data
greeting:		.asciiz	"Kaedon Hamm, Student of MIPS and Gaitros.\n" 
instructions:	.asciiz "Add, Subtract, Multiply, and Divide two numbers.\n"
firstNum:		.asciiz "Enter the first number: "
secondNum:		.asciiz "Enter the second number: "
addSym:			.asciiz " + "
subSym:			.asciiz " - "
mulSym:			.asciiz " * "
divSym:			.asciiz " / "
equSym:			.asciiz " = "
rmndr:			.asciiz " rem "
newline:		.asciiz "\n"
underOne:		.asciiz "I'm sorry, I cannot do that Hal. Your integer needs to be under 1."

		.text
main:
		# Print out first three lines of the program:
		# 	greeting, instructions, firstNum
		li		$v0, 4						# Loading the v0 register with '4' meaning that the machine should be expecting to print out a string
		la		$a0, greeting				# Preps the machine to print string 'greeting' to console
		syscall								# Execute the currently loaded a0
		la		$a0, instructions			# Preps the machine to print string 'instructions' to console
		syscall						
		la		$a0, firstNum				# Preps the machine to print string 'firstNum' to console
		syscall

		# Calls the read integer register
		#	and stores result into $t0
		li		$v0, 5						# Loading the v0 register with code '5' meaning that the machine should be expecting to read an input in
		syscall								# Machine is now waiting on an input
		move	$t0, $v0					# Whatever user inputs is stored into $t0

		slt 	$t3, $t0, 1					# Set Less Than compares $t0 to 1. If $t0 < 1 then $t3 = 0
		bne		$t3, $0, failure			# Branches off to another section of the program. In this case, if $t3 == 0 then skip to 'failure' branch

secondNum:
		# Asks for second integer, same set up as the previous section which requested for a user input
		li		$v0, 4
		la		$a0, secondNum
		syscall

		# Calls the read integer register
		#	and stores result into $t1
		li		$v0, 5
		syscall
		move	$t1, $v0

		slt 	$t3, $t1, 1
		bne		$t3, $0, failure


calcs:
# Addition Print out & calculations
		add		$t2, $t0, $t1				# $t0 and $t1 are being added together and stored in $t2
		li		$v0, 1						# Loading the v0 register with code '1' meaning that the machine should be expecting to print an integer to console
		move 	$a0, $t0					# Preps the machine to print out $t0
		syscall
		li		$v0, 4						# Loading the v0 register with code '4' for printing string
		la		$a0, addSym					# Preps the machine to print string 'addSym' to the console
		syscall
		li		$v0, 1						# Loading the v0 register with code '1' for printing integers
		move	$a0, $t1					# Preps the machine to print out $t1
		syscall
		li		$v0, 4						# Loading the v0 register with code '4' for printing strings
		la		$a0, equSym					# Preps the machine to print string 'equSym' to the console
		syscall
		li		$v0, 1						# Loading the v0 register with code '1' for printing integers
		move	$a0, $t2					# Preps the machine to print out $t2
		syscall
		li		$v0, 4						# Loading the v0 register with code '4' for printing strings
		la		$a0, newline				# Preps the machine to print string 'newline' to the console
		syscall

# Subtraction Print out & calculations
		sub 	$t2, $t0, $t1				# $t1 is taken from $t0 and the result is stored in $t2 (which overwrites the previous calculation's answer but that's fine)
		li		$v0, 1
		move 	$a0, $t0					# Next few lines are same as above and just used to print out the equation to the console
		syscall
		li		$v0, 4
		la		$a0, subSym
		syscall
		li		$v0, 1
		move	$a0, $t1
		syscall
		li		$v0, 4
		la		$a0, equSym
		syscall
		li		$v0, 1
		move	$a0, $t2
		syscall
		li		$v0, 4
		la		$a0, newline
		syscall

# Multiplication Print out & calculations
		li		$v0, 1						# Prints out lines to console first, calculations are completed further down
		move 	$a0, $t0
		syscall
		li		$v0, 4
		la		$a0, mulSym
		syscall
		li		$v0, 1
		move	$a0, $t1
		syscall
		li		$v0, 4
		la		$a0, equSym
		syscall
		mult	$t0, $t1					# $t0 and $t1 are multiplied together and the result is stored in mmfhi and mflo
		li		$v0, 1
		mflo	$a0							# Using mflo to print out the important bits of the answer. Mfhi is more used with division as seen later
		syscall
		li		$v0, 4
		la		$a0, newline
		syscall


# Division calculations & print to console
		li		$v0, 1						# Prints out lines to console first, calculations are completed further down
		move 	$a0, $t0
		syscall
		li		$v0, 4
		la		$a0, divSym
		syscall
		li		$v0, 1
		move	$a0, $t1
		syscall
		li		$v0, 4
		la		$a0, equSym
		syscall
		div		$t0, $t1					# #t0 is divided by $t1 and the result is stored in mfhi and mflo
		li		$v0, 1
		mflo	$a0							# mflo stores the significant bits. For example, $t0 = 21 and $t1 = 5, then mflow = 4
		syscall
		li		$v0, 4
		la		$a0, rmndr			
		syscall
		div		$t0, $t1
		li		$v0, 1
		mfhi	$a0							# Whereas mfhi hold the insignificant bits such as the remainder (example continued) mfhi = 1.
		syscall
		jr $ra

failure:									# This is where the program branches to when an entered variable is less than 1
		li		$v0, 4
		la		$a0, underOne
		syscall
		li		$v0, 10						# Loads the v0 register with code '10' for exit
		syscall
		jr $ra