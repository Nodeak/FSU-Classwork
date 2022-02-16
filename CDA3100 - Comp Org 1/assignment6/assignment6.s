
# ##################################################################################
# # File: sudoku.s                                                                 #
# # Description:   Query the user for a file name. We assume it must be a complete #
# #    path name since we cannot anticipate where QTSPIM will expect a local file. #
# #    The routine (OFile) will read in the filename and try to open it.  If       #
# #    cannot it will continue to ask the user for a valid filename.  Once         #
# #    successful, the file point will be passed back to the calling routine.      #

# # Author:  Dr. David A. Gaitros                                                  #
# # Date:  June 25th, 2018                                                         #
# # Copyright:  This code is property of FSU Department of Computer Science,       #
# #    written by Dr. David A. Gaitros for the sole use of students taking         #
# #    courses at the University.  Distrubution is not authorized.                 #
# #################################################################################


				.data
Hello:  		.asciiz "Hello,Enter a file name: \n"
				.align 2
NoFile: 		.asciiz "Error encountered, file did not open\n" 
OkFile: 		.asciiz "File was opened\n"
NXTLN:			.asciiz "\n"
Filen:  		.space  256			# Set aside 256 Characters
EOL:    		.byte '\n'
				.align 2
sudoku:			.space 164
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
	li			$v0,4
	la			$a0,sudoku
	syscall
	j			newEnding		# Jump to newEnding


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
	lb			$t5,0($t4)		# load byte into $t5
	li			$s5,10			# Load line feed in $s5
	beq			$t5,$s5,Done		# Go to Done when line feed found
	addiu		$t4,$t4,1		# Get next byte
	j			GetB			
Done:
	li			$s5,0			# Load zero (null character) into $s5
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
newEnding:
	li			$t0, 9			# row counter (doesn't get reset)
loop1:
	li			$t1, 9			# column counter (resets to 9 when new row appears)
	beqz		$t0, fullEnd	# when row counter == 0 jump to fullEnd
	addi		$t0,$t0,-1
loop2:
	lb			$t2, 0($a0)		# loads first byte from address in a0
	beqz		$t1, loop1		# when t1 == 0 jump back to loop1 to reset column counter
	add			$a0, $a0, 1
	addi		$t1, $t1, -1
fullEnd:
	jr			$ra
