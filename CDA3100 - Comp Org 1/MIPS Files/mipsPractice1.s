	    .data
MSG1:	.asciiz "Hello World!\n"
	    .text
	    .globl main
main:
	    li      $s1,7
	    li      $s2,3
	    div     $s1,$s2
        mflo    $s1
        mfhi    $s2
        li      $a0,$s1
        move    $a0,$s1

        syscall
        
        li      $v0,11
        lb		$a0, EOL		# 
        syscall
        li      $v0,1
        move    $a0,$s2

	    syscall
	    jr $ra