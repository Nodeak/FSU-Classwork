
# #################################################################################
#  Kaedon Hamm																	  #
#  Comp Org 1																	  #
#  3/8/2019															              #
# #################################################################################


				.data
teest:			.asciiz "test\n"
Hello:  		.asciiz "Hello,Enter a file name: \n"
				.align 2
NoFile: 		.asciiz "Error encountered, file did not open\n" 
OkFile: 		.asciiz "File was opened\n"
ValSud:			.asciiz "Sudoku Puzzle is Valid."
InValSud:		.asciiz "Sudoku Puzzle is Invalid."	
STARTBAR:		.asciiz "| "
BAR:			.asciiz " | "
ENDBAR: 		.asciiz " |"
UNDERLINE:		.asciiz "| - | - | - | - | - | - | - | - | - |\n"
Filen:  		.space  164			# Set aside 256 Characters
EOL:    		.byte '\n'
				.align 2
sudoku:			.space 164
				.text
				.align 2
NullCh:  		.word  0			# Just in case we need a null character
					#     After the puzzle. 
				.align  2			# Align on full word boundar
				.text
				.globl main
main:
# ##################################################################################
#  Save the return address ($ra) and call the Open File function (Ofile).          #
# ##################################################################################
	addiu		$sp,$sp,-4		# Get space from the stack
	sw			$ra,0($sp)		# Store return address on stack
	la			$a0,Filen		# Load $a0 (parameter) with addres to store filename. 
	jal			OFile			# Call Open File
# ##################################################################################
# # Save the file pointer in saved register $s1.  Restore the return address       #
# # and stack pointer.                                                             #
# ##################################################################################
	move		$s1,$v0			# Save Filename pointer to $s1
	lw			$ra,0($sp)		# Restore return address
	addiu		$sp,$sp,4		# Restore stack pointer
	la			$a0,OkFile		# Get ready to print success message
	li			$v0,4			# Tell syscall to print a string
	syscall
	li			$v0,14
	move		$a0,$s1			# pass file pointer
	la			$a1,sudoku		# Where to store the data 
	li			$a2,164			# Size of buffer to read in
	syscall
	addiu		$sp,$sp,-4	# We get some stack space 
	sw			$ra,0($sp)	# Preserve the return address
	jal			PRTMTX		# Call the Print Matrix Subroutine
	lw			$ra,0($sp)	# Restore the return address
	addiu		$sp,$sp,4	# Restore the stack space 
	addiu		$sp,$sp,-4
	sw			$ra,0($sp)
	jal			CHECKROWS
	lw			$ra,0($sp)	# Restore the return address
	addiu		$sp,$sp,4	# Restore the stack space 
	jr			$ra



#_________________________________________START OF READ FILE___________________________________________________________
# ###################################################################################
# Function to read from standard input a filename and open a file.                  #
# Send the address of where to store the filename in $a0.                           #
# Return the file pointer in $v0.                                                   #
# ###################################################################################
OFile:
	move		$t1,$a0			# Move address of where we want the file name to go to 
Again:					#    $t1
	li			$v0,4			# Tell syscall to print a string
	la			$a0,Hello		# Load address of string to print		
	syscall				# Print string
	move		$a0,$t1			# Load $a0 with the address of where we want the 
					#    Filename to go. 
	li			$a1,264			# Load max size of string
	li			$v0,8			# Tell syscall to read a string
	syscall				# Read a string


# ###################################################################################
# # Ok, we have read in a string.. Now we want to scan the string and find a line   #
# # feed (the number 10 or hex A) and replace it with binary zeros which is a       #
# # null character.                                                                 #
# ###################################################################################
 

	la			$t2,EOL			# EOL is the character after the filename 
								#    declaration. 
	sub			$t3,$t2,$t1		# Subtract the address of the EOL from 
								#    the address of the Filen to get the length
	move		$t4,$t1			# Put address of filename in $t4
GetB:	
	lb		$t5,0($t4)		# load byte into $t5
	li			$s5,10			# Load line feed in $s1
	beq			$t5,$s5,Done		# Go to Done when line feed found
	addiu		$t4,$t4,1		# Get next byte
	j			GetB			
Done:
	li			$s5,0			# Load zero (null character) into $s1
	sb			$s5,0($t4)		# Replace the line feed with null character


# ###################################################################################
# #  Try to open the file,  If it works move the file pointer to $v0 and return.    #
# #  If not, go back and read in another filename.                                  #
# ###################################################################################	


	li			$v0,13			# tell syscall to open a file
	move		$a0,$t1			# Move address of file in $a0
	li			$a1,0			# Open for reading
	li			$a2,0			# No purpose
	syscall				# Open file
	move    	$s6,$v0
	ble			$s6,$zero,Again		# Bad file, try it again. 
	move		$v0,$s6
	jr			$ra
#_________________________________________END OF READ FILE____________________________________________________



#_________________________________________START OF PRINT MATRIX_______________________________________________	
PRTMTX:

	la			$s0,sudoku	# Load address of Matrix into register $s0
	li			$s1,1		# Row Index - Every four byte
	li			$s2,1 		# Col Index - Every twenty bytes
	li			$t6,9		# Load number of rows and columns
	li			$v0,4
	la			$a0, STARTBAR
	syscall

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
	li			$t4,18		# Size of a row
	li			$t5,2		# Size of a col
	mul			$t1,$t1,$t4	# Get offset of Column
	mul			$t2,$t2,$t5	# Get offset of Row
	add			$s4,$s0,$t1	# Add the Row Offset
	add			$s4,$s4,$t2	# Add the Col Offset
	li			$v0,11		# Print an char
	lb			$a0,0($s4)	# Load the word
	syscall
	
	li			$t6,9		# Check if we have reached the end.
	div			$s2,$t6		# Divide column number by 5
	mfhi		$t6			# Remainder
	beqz		$t6,ENDROW	# At end of COL
	addiu		$s2,$s2,1	# Add one to the column
	li			$v0,4
	la			$a0,BAR
	syscall
	j			TOPPRT		# Get next Number

ENDROW:
	li			$v0, 4
	la			$a0, ENDBAR
	syscall
	li			$s2,1		# Reset Column Number
	li			$v0,11
	lb			$a0,EOL
	syscall
	li			$t6,9
	div			$s1,$t6		# Divide Row Number by 9
	mfhi		$t6
	beqz		$t6,DONEPRT
	addiu		$s1,$s1,1	# Add one to row number
	li			$v0,4
	la			$a0,UNDERLINE
	syscall
	la			$a0,STARTBAR
	syscall
	j			TOPPRT

DONEPRT:
	jr			$ra
#_____________________________________________END OF PRINT MATRIX_____________________________________



#_____________________________________________START OF CHECK ROWS_____________________________________
CHECKROWS:
	li			$s1,1		# Row Index - Every four byte
	li			$s2,1 		# Col Index - Every twenty bytes
	li			$t6,9		# Load number of rows and columns
	li			$s6,0
	

NXTCOLCR: 
	addiu		$t1,$s1,-1	# Normalize Row Number to 0-4
	addiu		$t2,$s2,-1	# Normalize Col Number to 0-4
	li			$t4,18		# Size of a row
	li			$t5,2		# Size of a col
	mul			$t1,$t1,$t4	# Get offset of Column
	mul			$t2,$t2,$t5	# Get offset of Row
	add			$s4,$s0,$t1	# Add the Row Offset
	add			$s4,$s4,$t2	# Add the Col Offset
	lb			$t1,0($s4)
	addi		$t1,$t1,-48	# converts char to int
	add			$s6,$s6,$t1		# adds current number to row's running total
	li			$t6,9		# Check if we have reached the end.
	div			$s2,$t6		# Divide column number by 9
	mfhi		$t6			# Remainder
	beqz		$t6,NXTROWCR	# At end of COL
	addiu		$s2,$s2,1	# Add one to the column
	j			NXTCOLCR		# Get next Number

NXTROWCR:
	li			$t7,45
	bne			$s6,$t7,NOTVAL
	li			$s2,1		# Reset Column Number
	li			$t6,9
	div			$s1,$t6		# Divide Row Number by 9
	mfhi		$t6
	beqz		$t6,CHECKCOLS
	addiu		$s1,$s1,1	# Add one to row number
	li			$s6,0
	j			NXTCOLCR
#_____________________________________________END OF CHECK ROWS_____________________________________

#_____________________________________________START OF CHECK COLS_____________________________________
CHECKCOLS:
	li			$s1,1		# Row Index - Every four byte
	li			$s2,1 		# Col Index - Every twenty bytes
	li			$t6,9		# Load number of rows and columns
	li			$s6,0
	

NXTROWCC: 
	addiu		$t1,$s1,-1	# Normalize Row Number to 0-4
	addiu		$t2,$s2,-1	# Normalize Col Number to 0-4
	li			$t4,18		# Size of a row
	li			$t5,2		# Size of a col
	mul			$t1,$t1,$t4	# Get offset of Column
	mul			$t2,$t2,$t5	# Get offset of Row
	add			$s4,$s0,$t1	# Add the Row Offset
	add			$s4,$s4,$t2	# Add the Col Offset
	lb			$t1,0($s4)
	addi		$t1,$t1,-48	# converts char to int
	add			$s6,$s6,$t1		# adds current number to row's running total
	li			$t6,9		# Check if we have reached the end.
	div			$s1,$t6		# Divide row number by 9
	mfhi		$t6			# Remainder
	beqz		$t6,NXTCOLCC	# At end of COL
	addiu		$s1,$s1,1	# Add one to the column
	j		 	NXTROWCC		# Get next Number

NXTCOLCC:
	li			$t7,45
	bne			$s6,$t7,NOTVAL
	li			$s1,1		# Reset Row Number
	li			$t6,9
	div			$s2,$t6		# Divide col Number by 9
	mfhi		$t6
	beqz		$t6,TOTVAL 
	addiu		$s2,$s2,1	# Add one to col number
	li			$s6,0
	j			NXTROWCC
#_____________________________________________END OF CHECK ROWS_____________________________________


#_____________________________________________START OF CHECK BLOCKS_________________________________
CHECKBLOCS:
	li			$t1,0		# starting point multiplier (will go up by 3's)
	li			$t2,0		# block number counter
	li			$s6,0		# block total
BLOCKLOOP:
	move		$t0,$s0		# starting address put into t0
	li			$t4,3
INNERLOOP:
	add			$t4,$t4,-1
	add			$t0,$t0,$t1 # applies new starting position offset
	lb			$t3,0($t0)  # loads byte from t0's position
	addiu		$t3,$t3,-48 # converts char into int
	add			$s6,$s6,$t3 # adds the number into the total
	add			$t0,$t0,2
	lb			$t3,0($t0)  # loads byte from t0's position
	addiu		$t3,$t3,-48 # converts char into int
	add			$s6,$s6,$t3 # adds the number into the total
	add			$t0,$t0,2
	lb			$t3,0($t0)  # loads byte from t0's position
	addiu		$t3,$t3,-48 # converts char into int
	add			$s6,$s6,$t3 # adds the number into the total
							# first row added up, going to next row and repeating
	add			$t0,$t0,14		# jumps to the next row for the current block
	bnez		$t4,INNERLOOP	# loops back into INNERLOOP
ENDING:
	li			$t7,45			
	bne			$s6,$t7,InValSud 	# checks if block adds up to 45
	add			$t1,$t1,3			# adds 3 to the base cursor to move it to the next blocks
	add			$t2,$t2,1			# adds 1 to the block counter
	li			$s6,0				# sets the block total counter back to 0	
	beq			$t2,9,ValSud		# checks to see if entire sudoku puzzle is finished successfully
	j			BLOCKLOOP
#_____________________________________________END OF CHECK BLOCKS___________________________________

#_____________________________________________VALID AND INVLAD STATEMENTS___________________________
TOTVAL:
	li			$v0,4
	la			$a0,ValSud			# jumps to success
	syscall
	jr			$ra					# jump to $ra
NOTVAL:
	li			$v0,4
	la			$a0,InValSud		# jumps to failure
	syscall
	jr			$ra
#_____________________________________________VALID AND INVLAD STATEMENTS___________________________