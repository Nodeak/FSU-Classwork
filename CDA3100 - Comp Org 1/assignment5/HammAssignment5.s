#################################################
#			Kaedon Hamm							#
#	Class:	CDA 3100							#
#	Date:	2.22.2019							#
#	Assignment: Read in positive integers until	#
#				a negative, find the sum, mean, #
#				max, min, and variance of the   #
#               set and print out accordingly   #
#################################################

            .data
MSG1:       .asciiz "Please enter 10 numbers\n"
MSG2:       .asciiz "The numbers you entered are: "
SUM:        .asciiz "\tSum: "
MAX:        .asciiz "\tMax: "
MIN:        .asciiz "\tMin: "
MEAN:       .asciiz "\tMean: "
VARI:       .asciiz "\tVariance: "
NXTLN:      .asciiz "\n"
DOT:        .asciiz "."
SPACE:      .byte   ' '     # '\n' for a carriage return
            .align  2
            .text
            .globl main
main:   
            li      $v0, 4
            la      $a0, MSG1
            syscall
            li      $s0, 0          # load the counter (s0) with 0
            li      $v0, 5          # tell syscall to read an int
            syscall                 # read an int
            move    $t0, $v0        # t0 is the newest inputted number
            blt     $t0,$0,results
            add     $s1,$s1,$t0     # s1 holds the sum of numbers
            add     $s0,$s0,1       # counter (for average of all numbers)
            move    $s2, $t0        # giving s2 (min) a base case
            move    $s3, $t0        # giving s3 (max) a base case 
sumNum:
            li      $v0, 5          # tell syscall to read an int
            syscall                 # read an int
            move    $t0, $v0        # t0 is the newest inputted number 
            blt     $t0,$0,results    # if t0 is less than 0, exit loop
            add     $s1,$s1,$t0     # s1 is holding the sum of numbers
            add     $s0,$s0,1       # counter (for average of all numbers)
            slt     $t1,$s2,$t0     # if s2 < t0, then t1 = 1
            beq     $t1,1,setMax    # if t1 = 1, then jump to 'setmax'
            slt     $t2,$t0,$s3     # if t0 < s3, then t1 = 0
            beq     $t2,1,setMin    # if t2 = 1, then jump to 'setmin'
            j       sumNum
setMax:
            move    $s2, $t0
            j       sumNum            # jump back to CODE
setMin:
            move    $s3, $t0
            j       sumNum
results:
            li      $v0, 4          # basic printing out strings
            la      $a0, SUM
            syscall
            li      $v0, 1
            move    $a0,$s1
            syscall
#
            li      $v0, 4
            la      $a0, NXTLN      # moving to next line
            syscall
#
            li      $v0, 4
            la      $a0, MAX
            syscall
            li      $v0, 1
            move    $a0,$s2
            syscall
#
            li      $v0, 4
            la      $a0, NXTLN
            syscall
#
            li      $v0, 4
            la      $a0, MIN
            syscall
            li      $v0, 1
            move    $a0,$s3
            syscall
#
            li      $v0, 4
            la      $a0, NXTLN
            syscall
#
            li      $v0, 4
            la      $a0, MEAN
            syscall
#
            div     $s1, $s0        # dividing s1 (sum) by s0 (counter) to recieve the mean
            li      $v0, 1
            mflo    $a0             # holds the important bits of the div result
            syscall
            li      $v0, 4
            la      $a0, DOT        # prints `.`
            syscall
            li      $v0, 1
            mfhi    $a0             # holds the less important bits of the div result
            syscall
#
            li      $v0, 4
            la      $a0, NXTLN
            syscall
#
            li      $v0, 4
            la      $a0, VARI       # could not figure out how to do the variance without an array
            syscall
            jr		$ra					# jump to $ra