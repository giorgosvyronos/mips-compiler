.data
.globl main

main:
li $t1,0
move $t0, $t1
$LOOP1:
$CONT1:
li $t1,0
bne $t0, $t1, $EXIT1
nop
li $t2,4
move $t0, $t2
j $LOOP1
nop
$EXIT1:
$EXIT_FUNC1:
jr $ra
nop

.data
