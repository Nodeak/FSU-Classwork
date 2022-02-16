#################################################
#			Kaedon Hamm							#
#	Class:	CDA 3100							#
#	Date:	3.27.2019							#
#	Assignment: Request a floating point number	#
#               and put it through multiple     #
#               functions to evaluate the cosine#
#################################################
    .data
num1:       .float 0.0
min:        .float 0.0
max:        .float 6.28318531
requestnum: .asciiz "\nPlease enter a floating point number: "
invalidnum: .asciiz "\nInvalid number, please re-enter."
results:    .asciiz "\nThe cosine is: "
    .text

main:

input:
    li.s     $f1, 0.0            # f1 = 0.0
    li.s     $f2, 6.28318531     # f2 = 6.2

    li      $v0, 4          
    la      $a0, requestnum # print requestnum
    syscall
    li      $v0, 6
    syscall
    s.s     $f0, num1       # f0 = user float number
    c.lt.s  $f0, $f1        # if f0 < f1
    bc1t    invalid         # jump to invalid
    c.lt.s  $f0, $f2        # if f0 > 6.2..
    bc1f    invalid         # jump to invalid

    mov.s   $f12, $f0       # f12 is being sent in as a variable to the cosine functions
    mov.s   $f4, $f0
    jal		cosine			# jump to cosine and save position to $ra
cosine:
    li      $s0, 0          # current exponent
    li      $s1, 12         # max exponent
    li.s    $f10, 1.0          # running total, starts at 1 because you sub and add from that
cloop:
    add     $s0, $s0, 2     # adding 2 to the current exponent
    move    $a0, $s0        # move s0 into an argument
    jal     power
    sub.s   $f10, $f10, $f12  # subtracting f12 from f3 (first run through is 1 - f12)
    add     $s0, $s0, 2     # adding 2 to the current exponent
    move    $a0, $s0        # move s0 into an argument
    jal     power
    add.s   $f10, $f12, $f10  # adding f12 to f3 (first run through is (f3-f12) + f12)
    beq     $s0, $s1, end   # branch to end if current exponent is equal to 12
    jal       cloop
power:
    move      $s6, $ra
    move      $s2, $a0          # s2 now is the exponent
    mov.s     $f12, $f4
    mov.s     $f1, $f12         # saving float into f1 to be multiplied
    li        $s3, 1            # counter
ploop:
    add     $s3, $s3, 1
    mul.s	$f12, $f12, $f1		# $f0 * $f0 = Hi and Lo registers
    beq     $s3, $s2, factorial
    j		ploop				# jump to ploop
factorial:
    move     $s3, $s2         # s3 is now 1 less than s2 (the exponent, which will be written over in floop)
floop:
    add     $s2, $s2, -1        # lower 'exponent' by 1
    mult    $s3, $s2    
    mflo    $s3                 # s3 = s3 * s2
    beq     $s2, 1, divide      # when the factorial is done being calc'd jump to divide
    j       floop
divide:
    mtc1    $s3, $f1           # making s3 into a floating point num
    cvt.s.w $f1, $f1
    div.s   $f12, $f12, $f1     # f12 = f1 / f12
    move    $ra, $s6
    jr      $ra
end:
    mov.s   $f12, $f3           # move total (f3) into f12 to be printed out
    li      $v0, 4
    la      $a0, results
    syscall
    li      $v0, 2
    mov.s   $f12, $f10
    syscall
    li      $v0, 10             # exit program
    syscall
    jr      $ra

invalid:
    li      $v0, 4
    la      $a0, invalidnum
    syscall
    j	    input				# jump to main