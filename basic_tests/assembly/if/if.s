.data
.globl main

main:
li $t1,0
move $t0, $t1
li $t1,0
bne $t0, $t1, $If_FALSE1
nop
li $t3,4
move $t2, $t3
J $If_EXIT2
nop
$If_FALSE1:
li $t3,5
move $t2, $t3
$If_EXIT2:
$EXIT_FUNC1:
jr $ra
nop

.data
