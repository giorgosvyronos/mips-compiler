.data
.globl main

main:
li $t1,0
move $t0, $t1
li $t3,0
move $t2, $t3
$LOOP1:
li $t1,4
bgt $t2, $t1, $EXIT1
nop
addiu $t0, $t0, 1
$CONT1:
addiu $t2, $t2, 1
j $LOOP1
nop
$EXIT1:
move $v0,$0
move v0 ,$t0
$EXIT_FUNC1:
jr $ra
nop

.data
