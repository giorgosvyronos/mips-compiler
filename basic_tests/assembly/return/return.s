.data
.globl main

main:
li $t1,0
move $t0, $t1
move $v0,$0
li $t1,2
add $t1,$t0,$t1
move v0 ,$t1
$EXIT_FUNC1:
jr $ra
nop

.data
