.data
.globl main

main:
li $t1,10
move $t0, $t1
$LOOP1:
$CONT1:
li $t1,0
blt $t0, $t1, $EXIT1
nop
li $t3,1
add $t3,$t0,$t3
move $t2, $t3
li $t3,2
bne $t2, $t3, $If_FALSE4
nop
j $EXIT1
nop
J $If_EXIT5
nop
$If_FALSE4:
$If_EXIT5:
subi $t0, $t0, 1
j $LOOP1
nop
$EXIT1:
$EXIT_FUNC1:
jr $ra
nop

.data
