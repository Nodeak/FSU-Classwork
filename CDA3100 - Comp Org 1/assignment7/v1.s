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
test:       .asciiz "\ntest\n"
yuh:       .asciiz "\nyuh\n"
tee5:       .asciiz "\ns5: " 
tee6:       .asciiz "\ns6: "
    .text
main:

input:
    l.s     $f1, min        # f1 = 0.0
    l.s     $f2, max        # f2 = 6.2

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
    jal		cosine			# jump to cosine and save position to $ra

    li      $v0, 10
    syscall
    jr      $ra

cosine:
    li      $s0, 0          # t0 = 0 , exponent/factorial *goes up by 2 until 12*
    li      $s1, 12         # t1 = 12 , max exponent/factorial value
    li      $s2, 1          # t3 = 1 , all the numbers are subtracted/added to this register
cloop:
    add     $s0, $s0, 2     # adding 2 to exponent (after first, t0 should be 4)
    move    $a0, $s0
    jal     power
    move    $a0, $v0
    jal     factorial
    move    $t3, $v0        # t3 = v0 , returned x^y/y! to t3
    sub     $s2, $t3, $s2   # subtracting ^ from s0 (should start out as 1-returnedNum)
    beq		$s0, $s1, end	# if $t0 ==t1 , branch to end

    add     $s0, $s0, 2     # adding 2 to exponent (after first, t0 should be 4)
    move    $a0, $s0
    jal     power
    move    $t3, $v0        # t3 = v0 , returned x^y/y! to t3
    add     $s2, $t3, $s2   # subtracting ^ from s0 (should start out as 1-returnedNum)
    beq		$s0, $s1, end	# if $t0 == t1, branch to end 
    j       cloop
power:
    move    $s7, $ra
    li      $s3, 1      # multiplication counter
    move    $t4, $a0    # t4 = 2 , exponent
    mov.s   $f0, $f12
    jal     ploop
ploop:
    beq     $s3, $t4, factorial  # when t2 == t4 (counter == exponent) branch to ploopfin   
    mul.s   $f0, $f0, $f0       # multiply the floating point by itself 
    add     $s3, $s3, 1         # add 1 to the counter
    j       ploop               # loops ploop
factorial:
    move    $s5, $t4
    add     $s6, $s5, -1
    jal     floop
floop:
    li      $t0, 1
    mult    $s5, $s6
    mflo    $s5
###################################
    li      $v0, 4
    la     $a0, tee5
    syscall
    li      $v0, 1
    move    $a0, $s5
    syscall
    li      $v0, 4
    la     $a0, tee6
    syscall
    li      $v0, 1
    move    $a0, $s6
    syscall
#################################

    beq     $s6, $t0, divide
    add     $s6, $s6, -1
    j       floop
    #li      $v0, 10
    #syscall
    #jr      $ra
divide:
    move    $a0, $s5
    mtc1    $a0, $f12
#    cvt.s.w $f12, $f12
    div.s   $f0, $f0, $f12
    move    $ra, $s7
    jr      $ra
end:
    li      $v0, 4
    la      $a0, results
    syscall
    li      $v0, 6
    syscall


    li      $v0, 10
    syscall
    jr      $ra

invalid:
    li      $v0, 4
    la      $a0, invalidnum
    syscall
    j	    input				# jump to main