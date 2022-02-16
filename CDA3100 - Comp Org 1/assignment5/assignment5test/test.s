# Project notes
# Design ideas
# 1. Hello World
# 2. Pass array in $a0
#       Count # of elements -> $v0
#       Read elements
#       Check to see if it is negative
#           - Stack 
# 3. Print array

# store 10 number
# put them into an array
# print them out

            .data
NUMBRS:     .space  40      # alternative to .word 0:10
MSG1:       .asciiz "Please enter 10 numbers\n"
ARRSUM:     .asciiz "\n\tSum: "
SPACE:      .byte   ' '     # '\n' for a carriage return
            .align  2
            .text
            .globl main
main:   
            li  $s7, 0
            li $v0, 4
            la $a0, MSG1
            syscall

# call a routine to read the numbers in
# pass the address of the array i $a0
            la      $a0, NUMBRS     # load the address of array in $a0
            add     $sp,$sp,-4      # get address from stack space
            sw      $ra,0($sp)      # store $ra
            jal     GETNUM          # jump to 
            lw		$ra,0($sp)		# restore return address
            addiu   $sp,$sp,4       # give stack space back           
            
            la      $a0, NUMBRS     # load address of array in $a0
            addiu   $sp,$sp,-4      # get address from stack space
            sw      $ra,0($sp)      # store $ra
            lw      $ra,0($sp)      # restore return address
            addiu   $sp,$sp,4       # give the stack space back

            jr      $ra
GETNUM:
            move 	$s1,$a0         # preserve the parameter
            li      $s2, 0         # load the counter with 0
NNUM:
            li      $v0, 5          # tell syscall to read an int
            syscall                 # read an int
            move    $s3,$s2
            bltz    $v0, SUM       # when a negative number has been read in,
                                    # jump to NSUM without storing it
            sw      $v0, 0($s1)     # store the word into the array
            addiu   $s1,$s1, 4      # position to next element
            addiu   $s2,$s2,1      # subtract one from counter
            bnez    $s2,NNUM        
            jr      $ra
SUM:
            lw      $t0, 0($s1)         #load value at addr a0 to t0
            add     $t1, $t1, $t0       # sum = sum + array[i]
            li      $v0, 1
            move    $a0, $t0
            syscall
            add     $t1,$t1,$t0
            addi    $s1, $s1, 4        # add addr by 4 to get the address of   next value in the array
            addiu   $s3,$s3,-1
            bnez    $s3, SUM
            li      $v0, 1
            move    $a0, $s5
            syscall
FINISH:
        li          $v0, 10    # exit
        syscall