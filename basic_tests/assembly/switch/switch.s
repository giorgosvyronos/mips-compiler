.data
.globl main

main:
li $t1,2
move $t0, $t1
$CASE2:
li $t2,0
bne $t2, $t1, $CASE3
nop
li $t3,0
move $t2, $t3
$CASE3:
li $t3,1
bne $t3, $t1, $CASE4
nop
li $t3,1
move $t0, $t3
$CASE4:
li $t3,2
bne $t3, $t1, $CASE5
nop
move $v0,$0
li $v0,2
$CASE5:
li $t3,3
move $t2, $t3
$EXIT1:
$EXIT_FUNC1:
jr $ra
nop

.data
