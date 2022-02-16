            .data
NUMBRS:     .space  40      # alternative to .word 0:10
MSG1:       .asciiz "Please enter 10 numbers\n"
MSG2:       .asciiz "The numbers you entered are: "
SPACE:      .byte   ' '     # '\n' for a carriage return
            .align  2
            .text
            .globl main
main:   
            li      $v0, 4
            la      $a0, MSG1
            syscall
            li      $s3,0

# call a routine to read the numbers in
# pass the address of the array i $a0
            la      $a0, NUMBRS     # load the address of array in $a0
            add     $sp,$sp,-4      # get address from stack space
            sw      $ra,0($sp)      # store $ra
            jal     GETNUM          # jump to 
            lw		$ra, 0($sp)		# restore return address
            addiu   $sp,$sp,4       # give stack space back           
            
            la      $a0, NUMBRS     # load address of array in $a0
            addiu   $sp,$sp,-4      # get address from stack space
            sw      $ra,0($sp)      # store $ra
            jal     PRTNUM          # call PRTNUM
            lw      $ra,0($sp)      # restore return address
            addiu   $sp,$sp,4       # give the stack space back

            jr      $ra

GETNUM:
            move 	$s1,$a0         # preserve the parameter
            li      $s2, 10         # load the counter with 10
NNUM:
            li      $v0, 5          # tell syscall to read an int
            syscall                 # read an int
            sw      $v0, 0($s1)     # store the word into the array
            bltz    $v0, PRTARR     # if v0 is less than 0, jump to PRTNUM
            addiu   $s1,$s1, 4      # position to next element
            addiu   $s2,$s2,1       # add one to counter
            bnez    $s2,NNUM        
            jr      $ra
PRTARR:
            lw      $s0, 0($s1)
            li      $v0, 1
            move    $a0, $s0
            syscall
            addiu   $s1,$s1,4
            addiu   $s2,$s2,-1
            bnez    $s2, PRTARR
            jr      $ra